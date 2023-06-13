#include "DynamixelPolitocean.h"
#include <Ethernet.h>
#include <string.h>
#include "Adafruit_MQTT_Client.h"
#include "setLED.h"     //lib to control the ON BOARD LED


////////////////////////////ATMEGA328 TQFP USED PINS///////////////////////////////
///////////// CLAW DIR          : 11 (PD7)  ==> ARDUINO PIN : 7
///////////// CLAW PWM          : 10 (PD6)  ==> ARDUINO PIN : 6
///////////// WRIST DIR         : 9  (PD5)  ==> ARDUINO PIN : 5
///////////// WRIST STEP        : 2  (PD4)  ==> ARDUINO PIN : 4
///////////// WRIST EN          : 23 (PC0)  ==> ARDUINO PIN : A0
///////////// IO1               : 32 (PD2)  ==> ARDUINO PIN : 2
///////////// IO2               : 1  (PD3)  ==> ARDUINO PIN : 3
///////////// STATUS_LED        : 25 (PC2)  ==> ARDUINO PIN : 16



/////////////******* ETHERNET PARAMETERS ******///////////////
#define MQTT_TIMEOUT 30             // milliseconds
#define MQTT_CONNECT_RETRY_DELAY 15 // milliseconds
#define AIO_SERVER "10.0.0.254"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "arm_board"

unsigned char mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x06};
IPAddress addr(10, 0, 0, 10);
EthernetClient ethClient;

// definition of the function to connect/reconnect to the mqtt server
Adafruit_MQTT_Subscribe *subscription;
Adafruit_MQTT_Client mqtt(&ethClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME);
Adafruit_MQTT_Subscribe commands = Adafruit_MQTT_Subscribe(&mqtt, "commands/");
int dim = 0;
void MQTT_connect();


/////////////******* SHOULDER PARAMETERS ******///////////////
#define SHOULDER_STEPS 20   
#define IO1 2               //PORT D    REED SWITCH
#define IO2 3               //PORT D

DynamixelPolitocean dxl(Wire, 0x4D, 1);

typedef enum{DOWN = -1, STOP = 0, UP = 1} arm_direction;
arm_direction direction = STOP;

volatile bool endrun = 0;         //FLAG TO CHECK IF SENSOR IS ACTIVE
float GR = 3.8;     //GEAR RATIO
int POSMAX,POSMIN,futurePos;
float max_angle = 100.0;    //MAX ANGLE OF MOBILITY ADMITTED BY THE SHOULDER
int findLimit(int posInit, float max_angle);
volatile char TOP_switch,BOTTOM_switch = 0; 
char endcal = 0;            //FLAG TO INDICATE END OF CALIBRATION

//PIN of the WS2812 LED
#define STATUS_LED 2        //PORT C


/////////////******* WRIST PARAMETERS ******///////////////
#define STEPS 20
//Direction pin
#define WRIST_DIR 5         //PORT D
//Step pin
#define WRIST_STEP 4        //PORT D
//enable pin (active low)
#define WRIST_EN 0          //PORT C


typedef enum{CCW_wrist = -1, STOP_W = 0, CW_wrist = 1} wrist_rotation;
wrist_rotation rotation = STOP_W;


/////////////******* CLAW PARAMETERS ******///////////////
#define CLAW_DIR 7          //PORT D
#define CLAW_PWM 6          //PORT D    USED FOR PWM GENERATION, TIMER 0 CHANNEL A (OC0A LEVEL)

void setCLAW_PWM(char value);


void calibrate(){
  //ISR
  dxl.setVelocity(0);               //STOP THE SHOULDER
  endrun = 1;                      //SHOULDER HAS REACHED THE SWITCH
}

void TOP()
{
  TOP_switch = (PIND & 0x04) >> 2;    //READ STATUS OF SWITCH 1
}

void BOTTOM()
{
  BOTTOM_switch = (PIND & 0x08) >> 3;   //READ STATUS OF SWITCH 2
}
  
void setup() {

  Ethernet.init(10);        
  Ethernet.begin(mac, addr);
 

  //Serial.begin(9600);
  mqtt.subscribe(&commands);

  
  //PINS CONFIGURATION
  //DDR  DIRECTION : 0 ==> INPUT, 1 ==> OUTPUT
  //PORT : OUTPUT SIGNAL : 0 ==> LOW, 1 ==> HIGH

  DDRD &= ~(1 << IO1);       //FINECORSA AS INPUTS, SO WE WRITE 0 TO THE RELATIVE PINS
  DDRD &= ~(1 << IO2);

  DDRD |= (1 << CLAW_DIR);     //CLAW PINS AS OUTPUT
  DDRD |= (1 << CLAW_PWM);     
  DDRD |= (1 << WRIST_DIR);    //WRIST PINS AS OUTPUT
  DDRD |= (1 << WRIST_STEP);
  DDRC |= (1 << WRIST_EN);     
  DDRC |= (1 << STATUS_LED);     

  //CONFIGURING FAST PWM ON CLAW_PWM PIN, CORRESPONDING TO PD6 (TIMER 0, CHANNEL A)
  TCCR0A |= (1 << 7);                 //SET COM0A1 ==> PWM in NON-INVERTING MODE 
  TCCR0A |= (1 << 0) | (1 << 1);      //SET WGM00,WGM01  ==> FAST PWM MODE, frequencyPWM = 62.5 KHz


  //DISABLE WRIST
  PORTC |= (1 << WRIST_EN);    //ENABLE HIGH ==> INACTIVE




/////////////******* RED LED ******///////////////
  setLED(255,0,0);

  
  //Serial.begin(9600);
  dxl.begin(57600);
  attachInterrupt(PD2, calibrate, FALLING);

  //1 SET WHEEL MODE AND SLIGHLTY ROTATE UNTIL SWITCH
  
  dxl.setOperatingMode(WHEEL);
  dxl.setVelocity(0);               //STOP THE SHOULDER

  MQTT_connect();

  
  //WAITING FOR THE CALIBRATION COMMAND
  while((subscription = mqtt.readSubscription(MQTT_TIMEOUT)) && endcal == 0){     


    //STAY IN THIS LOOP UNTIL THE CALIBRATION COMMAND IS NOT RECEIVED
    //1 WHEEL MODE , rotate until limit switch has been reached
    //2 ISR to change to MULTITURN mode, calculate POSMAX, POSMIN

    
    dim = strlen((char *)commands.lastread); // read the lenght of the recived data
    char cmd[dim + 1]; // allocate a string to hold the read json string
    memcpy(cmd, (char *)commands.lastread, dim); // copy the json string into a variable
    cmd[dim] = '\0';
    
    if(strcmp(cmd,"START_CALIBRATION")==0){
      
/////////////******* YELLOW LED ******///////////////
      setLED(255,255,0);

      
/////////////******* CALIBRATION STARTS ******///////////////

      //GO SLOWLY UP UNTIL THE SENSOR IS ACTIVATED --> SHOULDER IS AT THE TOP
      dxl.setVelocityWheelMode(80, CW);         // go up UNTIL THE SENSOR
      while(endrun == 0);                       //wait until WE HAVE REACHED THE SENSOR --> INTERRUPT SETS FLAG (endrun) at 1
      //WAITING FOR ISR (calibrate())

/////////////******* TOP REACHED ******///////////////

      dxl.setVelocity(0);     //stop the motor
      dxl.setOperatingMode(MULTITURN);      //CHANGE MODE : WHEEL MODE --> MULTITURN (TO KNOW THE POSITION AND CALCULATE MAXIMUM ADMITTED VALUE)

      POSMAX = dxl.getPosition();             //GETTING ABSOLUTE TOP POSITION
      POSMIN = findLimit(POSMAX,max_angle);   //CALCULATING ABSOLUTE BOTTOM POSITION, GIVEN THE MAXIMUM RANGE ANGLE
      
      dxl.setVelocity(500);   //SET VELOCITY OF THE MOTOR AT HALF OF MAXIMUM 
      
      delay(100);

/////////////******* GO AT HALF POSITION ******///////////////
      dxl.setGoalPosition((POSMAX+POSMIN)/2);   //GOING AT HALF POSITION
      delay(4000);                              //WAITING FOR THE SHOULDER TO GO AT CENTER POSITION

        
/////////////******* CALIBRATION ENDED ******///////////////

      //INSERT HERE THE FEEDBACK MESSAGE TO THE GUI








      endcal = 1;   //EXIT THE WHILE LOOP
      
    }
  }


/////////////******* GREEN LED ******///////////////
  setLED(0,255,0);

      
  //CALIBRATION ENDED, DETACH ISR TO THE CALIBRATE FUNCTION
  detachInterrupt(PD2);

  //ATTACHING ISR TO CHECK IF THE SHOULDER REACHED THE REED SWITCHES
  attachInterrupt(PD2,TOP,CHANGE);
  attachInterrupt(PD3,BOTTOM,CHANGE);
}

void loop() {

   
  MQTT_connect();     //WAITS UNTIL THERE IS CONNECTION WITH THE MQTT BROKER
  while((subscription = mqtt.readSubscription(MQTT_TIMEOUT))){
  
    dim = strlen((char *)commands.lastread); // read the lenght of the recived data
    char cmd[dim + 1]; // allocate a string to hold the read json string
    memcpy(cmd, (char *)commands.lastread, dim); // copy the json string into a variable
    cmd[dim] = '\0';

    if(strcmp(cmd,"SHOULDER_UP")==0){
      direction = UP;
    }
    else if(strcmp(cmd,"SHOULDER_DOWN")==0){
      direction = DOWN;
    }
    else if(strcmp(cmd,"STOP_SHOULDER")==0){
      direction = STOP;
    }
    if(strcmp(cmd, "ROTATE WRIST CCW")==0){
      rotation = CCW_wrist;
    }
    else if(strcmp(cmd, "ROTATE WRIST CW")==0){
      rotation = CW_wrist;
    }
    else if (strcmp(cmd, "STOP WRIST")==0){
      rotation = STOP_W;
    }
    if (strcmp(cmd, "OPEN NIPPER")==0){
      PORTD |= (1 << CLAW_DIR);       //DIRECTION = HIGH
      setCLAW_PWM(254);
    }
    else if(strcmp(cmd, "STOP NIPPER")==0) {
      setCLAW_PWM(0);                     //STOP ACTUATOR
    }
    else if (strcmp(cmd, "CLOSE NIPPER")==0){
      PORTD &= ~(1 << CLAW_DIR);       //DIRECTION = LOW
      setCLAW_PWM(254);
    }

  }


/////////////******* SHOULDER ******///////////////

  if(direction!=STOP){
    /////////////******* UP ******///////////////
        if(direction == UP && (TOP_switch == 0))
        {
          //ENTER ONLY IF REED SWITCH IS OFF
          futurePos = dxl.getPosition() + SHOULDER_STEPS;
          if(futurePos < (POSMAX - 10))
          {
            //GO UP ONLY IF FUTURE POSITION IS LESS THAN POSMAX (REDUCED BY 10 FOR SAFETY)
            dxl.setGoalPosition(futurePos);   //GO TO THAT POSITION
          }

          
    /////////////******* DOWN ******///////////////
        }
        else if(direction == DOWN && (BOTTOM_switch == 0))
        {
          //ENTER ONLY IF REED SWITCH IS OFF
          futurePos = dxl.getPosition() - SHOULDER_STEPS;
          if(futurePos > (POSMIN + 10))
          {
            //GO DOWN ONLY IF FUTURE POSITION IS MORE THAN POSMIN (INCREASED BY 10 FOR SAFETY)
            dxl.setGoalPosition(futurePos);   //GO TO THAT POSITION
          }
        }
  }


/////////////******* WRIST ******///////////////
  if(rotation!=STOP_W){
      //ENABLING THE WRIST MOTOR
      PORTC &= ~(1 << WRIST_EN);    //ENABLE LOW ==> ACTIVE

      //SETTING DIRECTION PIN
      if(rotation == CW_wrist)
        {
          //set WRIST_DIR = CW = HIGH
          PORTD |= (1 << WRIST_DIR);
        }
      else  PORTD &= ~(1 << WRIST_DIR);              //set WRIST_DIR = CCW = LOW

      for(int i=0;i<STEPS;i++){
        
        //SQUAREWAVE IN THE STEP PIN. 1 FOR EACH STEP
        PORTD |= (1 << WRIST_STEP);                    //digitalWrite(WRIST_STEP, HIGH);
        delay(1);
        PORTD &= ~(1 << WRIST_STEP);                   //digitalWrite(WRIST_STEP, LOW);
        delay(1);
      }
      
  }
  else{
    PORTC |= (1 << WRIST_EN);    //ENABLE HIGH ==> INACTIVE
  }
     
}


void MQTT_connect()
{
  // Stop if already connected.
  if (mqtt.connected())
  {
    return;
  }

  while (mqtt.connect() != 0)
  {
    // connect will return 0 for connected
    mqtt.disconnect();
    delay(MQTT_CONNECT_RETRY_DELAY);
  }
}

void setCLAW_PWM(char value)
{
  //CLAW_PWM pin is D6, connected to CHANNEL A - TIMER 0
  //OCR0A CONTAINS THE VALUE THAT IS CONSTANTLY COMPARED WITH THE COUNTER

  //NON INVERTING MODE ==> WHEN TCNT0 = OCR0A ==> PD6 = 0; PD6 = 1 WHEN TCNT0 == 255

  OCR0A = value;    //writing value from 0 to 255
}

int findLimit(int posInit,float max_angle)
{

  float DELTA = max_angle / 360.0;
  DELTA = DELTA * GR * 4095.0;
  return (posInit - (int)DELTA);    //CHECK IF IS + OR -,DEPENDING ON TESTS
}

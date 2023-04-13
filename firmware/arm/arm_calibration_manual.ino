#include <DynamixelPolitocean.h>
#include <Ethernet.h>
#include <string.h>
#include "Adafruit_MQTT_Client.h"


#define MQTT_TIMEOUT 30             // milliseconds
#define MQTT_CONNECT_RETRY_DELAY 15 // milliseconds
#define AIO_SERVER "10.0.0.254"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "arm_board"

typedef enum{DOWN = -1, STOP = 0, UP = 1} arm_direction;
typedef enum{CCW_wrist = -1, STOP_W = 0, CW_wrist = 1} wrist_rotation;

DynamixelPolitocean dxl(Wire, 0x4D, 1);
////////////////////////////ATMEGA328 TQFP USED PINS///////////////////////////////
///////////// CLAW DIR          : 11 (PD7)  ==> ARDUINO PIN : 7
///////////// CLAW PWM          : 10 (PD6)  ==> ARDUINO PIN : 6
///////////// WRIST DIR         : 9  (PD5)  ==> ARDUINO PIN : 5
///////////// WRIST STEP        : 2  (PD4)  ==> ARDUINO PIN : 4
///////////// WRIST EN          : 23 (PC0)  ==> ARDUINO PIN : A0
///////////// IO1               : 32 (PD2)  ==> ARDUINO PIN : 2
///////////// IO2               : 1  (PD3)  ==> ARDUINO PIN : 3
///////////// STATUS_LED        : 25 (PC2)  ==> ARDUINO PIN : 16


//1 WHEEL MODE , rotate until limit switch has been reached

//2 ISR to change to MULTITURN mode, calculate POSMAX, POSMIN, ADJUST OFFSET(IF NEEDED)

  
#define IO1 2               //PORT D
#define IO2 3               //PORT D
#define CLAW_DIR 7          //PORT D
#define CLAW_PWM 6          //PORT D    USED FOR PWM GENERATION, TIMER 0 CHANNEL A (OC0A LEVEL)
#define STEPS 20
//Direction pin
#define WRIST_DIR 9         //PORT D
//Step pin
#define WRIST_STEP 4        //PORT D
//enable pin (active low)
#define WRIST_EN 0          //PORT C
//DIN of the WS2812 LED
#define STATUS_LED 2        //PORT C

int position = 0;
bool dir = 0;
int dim = 0;
volatile bool end_run = 0;         //FLAG TO CHECK IF SENSOR IS ACTIVE
unsigned char mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x06};


IPAddress addr(10, 0, 0, 10);
EthernetClient ethClient;

// definition of the function to connect/reconnect to the mqtt server
Adafruit_MQTT_Subscribe *subscription;
Adafruit_MQTT_Client mqtt(&ethClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME);
Adafruit_MQTT_Subscribe commands = Adafruit_MQTT_Subscribe(&mqtt, "commands/");

arm_direction direction = STOP;
wrist_rotation rotation = STOP_W;

// definition of the function to connect/reconnect to the mqtt server
void MQTT_connect();
void setCLAW_PWM(char value);

short initPos;
short outPos;

int POSMAX,POSMIN;
volatile char flag = 0;

int findLimit(int posInit, float max_angle);

void calibrate(){
  dxl.setVelocity(0);               //STOP THE SHOULDER
  end_run = 1;                      //SHOULDER HAS REACHED THE SWITCH
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
  
    //Serial.begin(9600);
    pinMode(PD2,INPUT);
    dxl.begin(57600);
    attachInterrupt(PD2, calibrate, FALLING);

    //Serial.println("calibrating beings .. ");
    //Serial.println("WHEEL MODE, velocity 100 CW");
    //1 SET WHEEL MODE AND SLIGHLTY ROTATE UNTIL SWITCH
    
    dxl.setOperatingMode(WHEEL);
    dxl.setVelocity(0);               //STOP THE SHOULDER
    //Serial.println("rotating");

    MQTT_connect();     //WAITS UNTIL THERE IS CONNECTION WITH THE MQTT BROKER
    while((subscription = mqtt.readSubscription(MQTT_TIMEOUT) && end_run == 1)){            
      //STAY IN THIS LOOP AS SOON AS THE SHOULDER HAS REACHED THE SENSOR
      //ONLY SHOULDER UP IS RECOGNIZED, OTHERS ARE IGNORED
      
      dim = strlen((char *)commands.lastread); // read the lenght of the recived data
      char cmd[dim + 1]; // allocate a string to hold the read json string
      memcpy(cmd, (char *)commands.lastread, dim); // copy the json string into a variable
      cmd[dim] = '\0';
      
      if(strcmp(cmd,"SHOULDER_UP")==0){
        direction = UP;
        if(end_run == 0){
          dxl.setVelocityWheelMode(80, CW);         // go up when you press, until limit switch
        }
      }
      else if(strcmp(cmd,"STOP_SHOULDER")==0){
        dxl.setVelocity(0);               //STOP THE SHOULDER
        direction = STOP;
      }

    }


    //START CALIBRATION SINCE THE TOP POSITION IS REACHED

    dxl.setVelocity(0);     //stop the motor
    dxl.setOperatingMode(MULTITURN);

    dxl.setVelocity(500);   //SET VELOCITY OF THE MOTOR AT HALF OF MAXIMUM, 
    delay(200);
    
    POSMAX = dxl.getPosition();      //GETTING ABSOLUTE TOP POSITION
    POSMIN = findLimit(POSMAX,50.0);   //CALCULATING ABSOLUTE BOTTOM POSITION, GIVEN THE MAXIMUM RANGE ANGLE


    delay(100);
//    Serial.println("Multi - Turn mode ON ");
//    Serial.print("POSMAX = ");
//    Serial.println(POSMAX);
//    Serial.print("POSMIN = ");
//    Serial.println(POSMIN);
//
//    Serial.print("RANGE = ");
//    Serial.println(POSMAX - POSMIN);     
    
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
  if(direction!=STOP){
        if(direction == UP)
        {
          dxl.setVelocityWheelMode(500,CW);
        }
        else if(direction == DOWN)
        {
          dxl.setVelocityWheelMode(500,CCW);
        }
  }
  else
  {
    dxl.setVelocity(0);       //STOP THE MOTOR
  }
  if(rotation!=STOP_W){
      PORTC &= ~(1 << WRIST_EN);    //ENABLE LOW ==> ACTIVE

      //SETTING DIRECTION PIN
      if(rotation == CW_wrist)
        {
          //set WRIST_DIR = CW = HIGH
          PORTD |= (1 << WRIST_DIR);
        }
      else  PORTD &= ~(1 << WRIST_DIR);              //set WRIST_DIR = CCW = LOW

      for(int i=0;i<STEPS;i++){
        
        //SQUAREWAVE INT THE STEP PIN. 1 FOR EACH STEP
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



int findLimit(int posInit,float max_angle)
{
  //inserting parameters
  float GR = 3.8;     //GEAR RATIO
  float DELTA = max_angle / 360.0;
  DELTA = DELTA * GR * 4095.0;
  return (posInit - (int)DELTA);    //CHECK IF IS + OR -,DEPENDING ON TESTS
}

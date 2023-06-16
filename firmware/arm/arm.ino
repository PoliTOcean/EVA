#include <DynamixelPolitocean.h>
#include <Ethernet.h>
#include <string.h>
#include "Adafruit_MQTT_Client.h"
#include "setLED.h"     //lib to control the ON BOARD LED


////////////////////////////ATMEGA328P TQFP USED PINS///////////////////////////////
///////////// CLAW DIR          : 11 (PD7)  ==> ARDUINO PIN : 7
///////////// CLAW PWM          : 10 (PD6)  ==> ARDUINO PIN : 6
///////////// WRIST DIR         : 9  (PD5)  ==> ARDUINO PIN : 5
///////////// WRIST STEP        : 2  (PD4)  ==> ARDUINO PIN : 4
///////////// WRIST EN          : 23 (PC0)  ==> ARDUINO PIN : A0
///////////// IO1               : 32 (PD2)  ==> ARDUINO PIN : 2
///////////// IO2               : 1  (PD3)  ==> ARDUINO PIN : 3
///////////// STATUS_LED        : 25 (PC2)  ==> ARDUINO PIN : 16



/////////////******* ETHERNET PARAMETERS ******///////////////
#define MQTT_TIMEOUT 1             // milliseconds
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
#define SHOULDER_STEPS 40  
#define CW_LIMIT 200  //70 degrees angle maximum range
#define CCW_LIMIT 3800
DynamixelPolitocean dxl(Wire, 0x4D, 1);

typedef enum{DOWN = -1, STOP = 0, UP = 1} arm_direction;
arm_direction direction = STOP;

uint16_t currentPos;
uint8_t err = 0;
unsigned char calib_done = 0, canstart = 0;

//PIN of the WS2812 LED
#define STATUS_LED 2        //PORT C


/////////////******* WRIST PARAMETERS ******///////////////
#define STEPS 70
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
  
void setup() {

  Ethernet.init(10);        
  Ethernet.begin(mac, addr);
 

  Serial.begin(9600);
  mqtt.subscribe(&commands);
  
  Serial.println("\nETHERNET CONNECTED");
  dxl.begin(57600);
  //PINS CONFIGURATION
  //DDR  DIRECTION : 0 ==> INPUT, 1 ==> OUTPUT
  //PORT : OUTPUT SIGNAL : 0 ==> LOW, 1 ==> HIGH

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


//CONFIGURING JOINT MODE ==> MAX RANGE (CW = 1, CCW = 4095)
  dxl.setCWAngleLimit(CW_LIMIT);
  dxl.setCCWAngleLimit(CCW_LIMIT);

  setLED(RED);
  dxl.TorqueOff();  //ALLOW THE MANUAL MOVEMENT OF THE SHOULDER
  
  delay(100);
   
   //INITIALIZED currentPos TO BOTTOM
   while(calib_done == 0)
   {
    MQTT_connect();     //WAITS UNTIL THERE IS CONNECTION WITH THE MQTT BROKER
    while((subscription = mqtt.readSubscription(MQTT_TIMEOUT))){
     
    dim = strlen((char *)commands.lastread); // read the lenght of the recived data
    char cmd[dim + 1]; // allocate a string to hold the read json string
    memcpy(cmd, (char *)commands.lastread, dim); // copy the json string into a variable
    cmd[dim] = '\0'; 
   
    if(strcmp(cmd,"START_CALIBRATION")==0 && canstart == 1)
      {
       currentPos = dxl.getPosition();
       if(currentPos == 128)
       {
        //ERROR DETECTED ==> ESTIMATE POSITION AT HALF RANGE ==> NEED TO GO AT TOP OR BOTTOM TO UPDATE THE POSITION CORRECTLY
        currentPos = (int)((CCW_LIMIT - CW_LIMIT)/2);
       }
       setLED(GREEN);
       calib_done = 1;
       dxl.setVelocity(500);
      }
    if(strcmp(cmd,"TORQUE_ON")==0)
      {
       dxl.TorqueOn();  //FIX POSITION OF THE SHOULDER
       setLED(YELLOW);
       canstart = 1;
      }
    if(strcmp(cmd,"TORQUE_OFF")==0)
      {
       dxl.TorqueOff();  //ALLOW THE MANUAL MOVEMENT OF THE SHOULDER
       setLED(RED);
       canstart = 0;
      }
    }
   }
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
      setLED(CIANO);
    }
    else if(strcmp(cmd,"SHOULDER_DOWN")==0){
      direction = DOWN;
      setLED(MAGENTA);
    }
    else if(strcmp(cmd,"STOP_SHOULDER")==0){
      direction = STOP;
      setLED(GREEN);
    }
    if(strcmp(cmd,"TORQUE_ON")==0)
    {
      dxl.TorqueOn();
      setLED(GREEN);
    }
    else if(strcmp(cmd,"TORQUE_OFF")==0)
    {
      dxl.TorqueOff();
      setLED(RED);
    }
    if(strcmp(cmd, "ROTATE WRIST CCW")==0){
      rotation = CCW_wrist;
      setLED(BLUE);
    }
    else if(strcmp(cmd, "ROTATE WRIST CW")==0){
      rotation = CW_wrist;
      setLED(ORANGE);
    }
    else if (strcmp(cmd, "STOP WRIST")==0){
      rotation = STOP_W;
      setLED(GREEN);
    }
    if (strcmp(cmd, "OPEN NIPPER")==0){
      PORTD |= (1 << CLAW_DIR);       //DIRECTION = HIGH
      setLED(YELLOW);
      setCLAW_PWM(254);
    }
    else if(strcmp(cmd, "STOP NIPPER")==0) {
      setCLAW_PWM(0);                     //STOP ACTUATOR
      setLED(GREEN);
    }
    else if (strcmp(cmd, "CLOSE NIPPER")==0){
      PORTD &= ~(1 << CLAW_DIR);       //DIRECTION = LOW
      setLED(WHITE);
      setCLAW_PWM(254);
    }
  }

  
/////////////******* SHOULDER ******///////////////

if(direction!=STOP)
  {
   delay(5);
  /////////////******* UP ******///////////////
   if(direction == UP)
     {
      currentPos -= SHOULDER_STEPS;
      err = dxl.setGoalPosition(currentPos);
      if(err == 8 || err == 2)
        {
         //Serial.println("RANGE ERROR");
         //OUT OF RANGE ERROR
         currentPos = CW_LIMIT;
         direction = STOP;
         dxl.setGoalPosition(currentPos);
         setLED(RED);
        }     
      
  /////////////******* DOWN ******///////////////
      }
  else
      {
       currentPos += SHOULDER_STEPS;
       err = dxl.setGoalPosition(currentPos);
       if(err == 8 || err == 2)
         {
          //OUT OF RANGE ERROR
          currentPos = CCW_LIMIT;
          direction = STOP;
          dxl.setGoalPosition(currentPos);
          setLED(RED);
         }  
      }
   }
/////////////******* WRIST ******///////////////
  if(rotation!=STOP_W)
  {
      //ENABLING THE WRIST MOTOR
    PORTC &= ~(1 << WRIST_EN);    //ENABLE LOW ==> ACTIVE

      //SETTING DIRECTION PIN
    for(int i=0;i<STEPS;i++)
    {
      if(rotation == CW_wrist)
      {
        //set WRIST_DIR = CW = HIGH
        PORTD |= (1 << WRIST_DIR);
      }
      else  PORTD &= ~(1 << WRIST_DIR);              //set WRIST_DIR = CCW = LOW

      //SQUAREWAVE IN THE STEP PIN. 1 FOR EACH STEP
      PORTD |= (1 << WRIST_STEP);                    //digitalWrite(WRIST_STEP, HIGH);
      delayMicroseconds(700);
      PORTD &= ~(1 << WRIST_STEP);                   //digitalWrite(WRIST_STEP, LOW);
      delayMicroseconds(700);
    }
  }
  else
  {
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

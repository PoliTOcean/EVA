#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
#include <Arduino_JSON.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define DEBUG_MOTORS 0                //Macro used to enable testing servos
#define DEBUG_JOYSTICK_INPUTS 0       //Macro used to enable testing joystick inputs
#define DEBUG_MOTORS_ROTATION 0       //Macro used to enable testing motors rotation direction

//Macro used to define contants used in the code
#define NUM_SERVO 8
#define MQTT_TIMEOUT 100              //milliseconds
#define MQTT_CONNECT_RETRY_DELAY 15   //milliseconds
#define ESC_DELAY 7000                //millisecons
#define MIN_INPUT_READING -32678      //Minimum input reading value from the joystick
#define MAX_INPUT_READING 32678       //Maximum input reading value from the joystick
#define MIN_MAPPED_VALUE 1700         //Minium value to which the joystick reading is mapped
#define MAX_MAPPED_VALUE 1300         //Maximum value to which the joystick reading is mapped
#define MAX_Z 1800
#define SERVO_OFF 1500                //Value to write in order to stop the servo
#define AIO_SERVER "10.0.0.254"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "nucleo-L432CK"

//definition of the function to connect/reconnect to the mqtt server
void MQTT_connect();

//motors position definition
typedef enum{RDX,FSX,FDX,UPRSX,RSX,UPFDX,UPFSX,UPRDX} motors_position_mapping;
/*
Motors:

  - RDX -> Rear Right
  - FSX -> Forward Left
  - FDX -> Forward Right
  - UPRSX -> Up Rear Left
  - RSX -> Rear Left
  - UPFDX -> Up Rear Right
  - UPFSX -> Up Forward Left
  - UPRDX -> Up Rear Right

See the ROV picture for a proper understanding of the motors mapping

*/

#if DEBUG_JOYSTICK_INPUTS
//                              RDX   FSX   FDX  UPRSX   RSX  UPFDX UPFSX UPRDX
int powVectorSTOP[NUM_SERVO] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
int powVectorForwardY[NUM_SERVO] = {1700, 1500, 1500, 1500, 1700, 1500, 1500, 1500};
int powVectorReverseY[NUM_SERVO] = {1500, 1700, 1700, 1500, 1500, 1500, 1500, 1500};
int powVectorSXX[NUM_SERVO] = {1500, 1600, 1600, 1500, 1500, 1500, 1500, 1600};
int powVectorDXX[NUM_SERVO] = {1600, 1500, 1500, 1600, 1500, 1500, 1500, 1500};
#endif

//servo related variables
Servo servo[NUM_SERVO];
unsigned char servoPin[NUM_SERVO] = {PA5, PA3, PA4, PA8, PA11, PA0, PA2, PB1};

//mac and ip address definition
unsigned char mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x04};
IPAddress addr(10, 0, 0, 3);

//Axes realated variable
int X, Y, Z_U, Z_D, ROLL, PITCH, YAW;
int Z_URemap;
int Z_DRemap;
int YRemap;
int XRemap;
//int YRemap2;
//int XRemap2;
float xp, yp;
int val_xy;

//json parsing related variables
int dim;
char *cmd;
JSONVar commandsIn;

//mqtt and communication related variables
EthernetClient ethClient;
Adafruit_MQTT_Subscribe *subscription;
Adafruit_MQTT_Client mqtt(&ethClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME);
Adafruit_MQTT_Subscribe motors = Adafruit_MQTT_Subscribe(&mqtt, "axes/");

void setup(){

  int i;

  Serial.begin(9600);
  Ethernet.init(D3);

  for (i = 0; i < NUM_SERVO; i++)
  {
    servo[i].attach(servoPin[i]);
    servo[i].writeMicroseconds(SERVO_OFF);
  }
  Ethernet.begin(mac, addr);        // start the Ethernet connection
  delay(ESC_DELAY);                 // delay to allow the ESC to recognize the stopped signal
  mqtt.subscribe(&motors);          // subscribe to the mqtt topic "axes/"
}

void loop(){

#if DEBUG_MOTORS
  servo[0].writeMicroseconds(1700);
  delay(6000);
  servo[0].writeMicroseconds(1500);
  delay(1000);
  servo[1].writeMicroseconds(1700);
  delay(6000);
  servo[1].writeMicroseconds(1500);
  delay(1000);
  servo[2].writeMicroseconds(1700);
  delay(6000);
  servo[2].writeMicroseconds(1500);
  delay(1000);
  servo[3].writeMicroseconds(1700);
  delay(6000);
  servo[3].writeMicroseconds(1500);
  delay(1000);
  servo[4].writeMicroseconds(1700);
  delay(6000);
  servo[4].writeMicroseconds(1500);
  delay(1000);
  servo[5].writeMicroseconds(1700);
  delay(6000);
  servo[5].writeMicroseconds(1500);
  delay(1000);
  servo[6].writeMicroseconds(1700);
  delay(6000);
  servo[6].writeMicroseconds(1500);
  delay(1000);
  servo[7].writeMicroseconds(1700);
  delay(5000);
  servo[7].writeMicroseconds(1500);
  delay(5000); 
#endif

#if DEBUG_MOTORS_ROTATION

  servo[RDX].writeMicroseconds(1700);
  delay(10000);
  servo[RDX].writeMicroseconds(SERVO_OFF);
  delay(3000);
  servo[FDX].writeMicroseconds(1700);
  delay(10000);
  servo[FDX].writeMicroseconds(SERVO_OFF);
  delay(3000);
  servo[FSX].writeMicroseconds(1700);
  delay(10000);
  servo[FSX].writeMicroseconds(SERVO_OFF);
  delay(3000);
  servo[RSX].writeMicroseconds(1700);
  delay(10000);
  servo[RSX].writeMicroseconds(SERVO_OFF);
  delay(3000);

#endif
  
  MQTT_connect();   //connect to the mqtt server

  while ((subscription = mqtt.readSubscription(MQTT_TIMEOUT))){
    if (subscription == &motors){
      dim = strlen((char *)motors.lastread);        //read the lenght of the recived data
      cmd = new char[dim+1];                        //allocate a string to hold the read json string
      memcpy(cmd, (char *)motors.lastread, dim);    //copy the json string into a variable
      cmd[dim] = '\0';
      commandsIn = JSON.parse(cmd);                 //parse the json file

      if (JSON.typeof(commandsIn) == "undefined"){  //check whether the command is correct
        /*
        Serial.println("Parsing input failed!");
        return;
        */
        continue;
      }

      //parse the values recived into the allocated variable
      Z_U = ((int)commandsIn["Z_UP"]);
      Z_D = ((int)commandsIn["Z_DOWN"]);
      ROLL = ((int)commandsIn["ROLL"]);
      PITCH = ((int)commandsIn["PITCH"]);
      YAW = ((int)commandsIn["YAW"]);
      Y = ((int)commandsIn["Y"]);
      X = ((int)commandsIn["X"]);

      //remap the recived values into a proper interval range, in order to process them
      Z_URemap = map(Z_U,MIN_INPUT_READING, MAX_INPUT_READING, SERVO_OFF, MAX_Z);
      Z_DRemap = map(Z_D,MIN_INPUT_READING, MAX_INPUT_READING, SERVO_OFF, MAX_Z);
      XRemap = map(X,MIN_INPUT_READING, MAX_INPUT_READING, MIN_MAPPED_VALUE, MAX_MAPPED_VALUE);
      YRemap = map(Y,MIN_INPUT_READING, MAX_INPUT_READING, MIN_MAPPED_VALUE, MAX_MAPPED_VALUE);
      //XRemap2 = 0.5 * sqrt(2 + XRemap*XRemap - YRemap*YRemap + 2*sqrt(2)*XRemap) - 0.5 * sqrt(2 + XRemap*XRemap - YRemap*YRemap - 2*sqrt(2)*XRemap);
      //YRemap2 = 0.5 * sqrt(2 - XRemap*XRemap + YRemap*YRemap + 2*sqrt(2)*Y) - 0.5 * sqrt(2 - XRemap*XRemap + YRemap*YRemap - 2*sqrt(2)*YRemap);


#if DEBUG_JOYSTICK_INPUTS
      //the following part is meant for testing and, thus, it does not represent the final implementation 
      //of the code
      //the folloing implementaton simply activates some of the motors based on the input direction,
      //regardless of the proper force that should be dispatched while inside the water
      //furthermore only x,y,z_up and z_down movments are implemented
      if (YRemap > 550)
      {
        servo[RDX].writeMicroseconds(1700);
        servo[RSX].writeMicroseconds(1700);
      }
      else if (XRemap > 450 && XRemap < 550 &&
      YRemap > 450 && YRemap < 550)
      {
        for (int i = 0; i < 8; i++)
        {
          servo[i].writeMicroseconds(powVectorSTOP[i]);
        }
      }
      else if (YRemap < 450)
      {
        servo[FSX].writeMicroseconds(1700);
        servo[FDX].writeMicroseconds(1700);
      }

      
      if (XRemap > 550)
      {
        servo[FSX].writeMicroseconds(1700);
        servo[RSX].writeMicroseconds(1700);
      }
      else if (XRemap > 450 && XRemap < 550 &&
      YRemap > 450 && YRemap < 550)
      {
        for (int i = 0; i < 8; i++)
        {
          servo[i].writeMicroseconds(powVectorSTOP[i]);
        }
      }
      else if (XRemap < 450)
      {
        servo[RDX].writeMicroseconds(1700);
        servo[FDX].writeMicroseconds(1700);
      }

      if (Z_URemap > 750)
      {
        servo[UPRSX].writeMicroseconds(1700);//orario
        servo[UPFDX].writeMicroseconds(1700);//orario
        servo[UPFSX].writeMicroseconds(1600);//antiorario
        servo[UPRDX].writeMicroseconds(1600);//antiorario
      }
      if (Z_DRemap > 750)//DOWN
      {
        servo[UPRSX].writeMicroseconds(1600);//orario
        servo[UPFDX].writeMicroseconds(1600);//orario
        servo[UPFSX].writeMicroseconds(1700);//antiorario
        servo[UPRDX].writeMicroseconds(1700);//antiorario
      }

      if (Z_DRemap < 750 && Z_URemap < 750)
      {
        servo[UPRSX].writeMicroseconds(1500);//orario
        servo[UPFDX].writeMicroseconds(1500);//orario
        servo[UPFSX].writeMicroseconds(1500);//antiorario
        servo[UPRDX].writeMicroseconds(1500);//antiorario
      }
 #endif

      //Motors directions driving

      //x-y axes
      xp = abs(XRemap-SERVO_OFF)/(1700-1300);
      yp = abs(YRemap-SERVO_OFF)/(1700-1300);
      val_xy = XRemap*(xp+0.5-yp)+YRemap*(yp+0.5-xp);
      servo[FDX].writeMicroseconds((val_xy>1550 || val_xy<1450)?val_xy:SERVO_OFF);
      servo[FSX].writeMicroseconds((val_xy>1550 || val_xy<1450)?3000-val_xy:SERVO_OFF);
      servo[RDX].writeMicroseconds((val_xy>1550 || val_xy<1450)?3000-val_xy:SERVO_OFF);
      servo[RSX].writeMicroseconds((val_xy>1550 || val_xy<1450)?3000-val_xy:SERVO_OFF);
  
      //z axes
      if(Z_URemap>=Z_DRemap){
        servo[UPFDX].writeMicroseconds(Z_URemap>=1600?Z_URemap:SERVO_OFF);
        servo[UPRSX].writeMicroseconds(Z_URemap>=1600?Z_URemap:SERVO_OFF);
        servo[UPRDX].writeMicroseconds(Z_URemap>=1600?3000-Z_URemap:SERVO_OFF);
        servo[UPFSX].writeMicroseconds(Z_URemap>=1600?3000-Z_URemap:SERVO_OFF);
      }
      else{
        servo[UPRDX].writeMicroseconds(Z_DRemap>=1600?Z_DRemap:SERVO_OFF);
        servo[UPFSX].writeMicroseconds(Z_DRemap>=1600?Z_DRemap:SERVO_OFF);
        servo[UPFDX].writeMicroseconds(Z_DRemap>=1600?3000-Z_DRemap:SERVO_OFF);
        servo[UPRSX].writeMicroseconds(Z_DRemap>=1600?3000-Z_DRemap:SERVO_OFF);
      }
    }
  }
}

//the following function is used in order to connect to mqtt server or reconnect to it
//in case the connection is lost:
//hence the function is called at the beginning of each iteration of the loop function
void MQTT_connect(){

  // Stop if already connected.
  if (mqtt.connected()){
    return;
  }

  while (mqtt.connect() != 0){ 
    // connect will return 0 for connected
    mqtt.disconnect();
    delay(MQTT_CONNECT_RETRY_DELAY);
  }
}

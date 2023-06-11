#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
#include <Arduino_JSON.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "control_allocation.h"
#include "joystick_mapper.h"
#include "lookuptable.h"
#include "pid.h"
#include "reference_change.h"

// Macro used to define contants used in the code
#define NUM_SERVO 8
#define MQTT_TIMEOUT 10             // milliseconds
#define MQTT_CONNECT_RETRY_DELAY 15 // milliseconds
#define ESC_DELAY 7000              // millisecons
#define MIN_INPUT_READING -32678    // Minimum input reading value from the joystick
#define MAX_INPUT_READING 32678     // Maximum input reading value from the joystick
#define MIN_MAPPED_VALUE 1760       // Minium value to which the joystick reading is mapped
#define MAX_MAPPED_VALUE 1200       // Maximum value to which the joystick reading is mapped
#define MAX_Z 1750
#define SERVO_OFF 1500 // Value to write in order to stop the servo
#define AIO_SERVER "10.0.0.254"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "nucleo-L432CK"
#define DELAY_PWM 0

#define kp 95.0
#define ki 5
#define kd 0.5

#define MAX_FORCE 80.0
#define MIN_FORCE 1.0
#define MIN_DISTANCE 0.001

#define MAX_SPEED 1.0
#define dt 0.03

#define map_pwm(X) X == 1500 ? 0.0 : ((X / (1900.0 + 1100.0)) * dt * MAX_SPEED * (X >= 1500 ? 1.0 : -1.0))

// definition of the function to connect/reconnect to the mqtt server
void MQTT_connect();
void pid_control();

// motors position definition
typedef enum
{
  FDX,
  RSX,
  RDX,
  UPRSX,
  FSX,
  UPFDX,
  UPFSX,
  UPRDX
} motors_position_mapping;
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
int powVectorSTOP[NUM_SERVO] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
int powVectorForwardY[NUM_SERVO] = {1700, 1500, 1500, 1500, 1700, 1500, 1500, 1500};
int powVectorReverseY[NUM_SERVO] = {1500, 1700, 1700, 1500, 1500, 1500, 1500, 1500};
int powVectorSXX[NUM_SERVO] = {1500, 1600, 1600, 1500, 1500, 1500, 1500, 1600};
int powVectorDXX[NUM_SERVO] = {1600, 1500, 1500, 1600, 1500, 1500, 1500, 1500};
#endif

// servo related variables
Servo servo[NUM_SERVO];
unsigned char servoPin[NUM_SERVO] = {PA6, PA3, PA4, PA8, PA11, PA0, PA2, PB1};

// mac and ip address definition
unsigned char mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x04};
IPAddress addr(10, 0, 0, 3);

// Axes realated variable
int X, Y, Z_U, Z_D, ROLL, PITCH, YAW;
int Z_URemap;
int Z_DRemap;
int YRemap;
int XRemap;
float YRemap2;
float XRemap2;
// int YRemap2;
// int XRemap2;
float xp,
    yp;
float valx1, valy1;
float valx2, valy2;
double depth;
double setPoint = 0.55;
// json parsing related variables
int dim;
char *cmd;
bool pid_on = true;
JSONVar commandsIn;
JSONVar sensorsIn;

// mqtt and communication related variables
EthernetClient ethClient;
Adafruit_MQTT_Subscribe *subscription;
Adafruit_MQTT_Client mqtt(&ethClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME);
Adafruit_MQTT_Subscribe sensors = Adafruit_MQTT_Subscribe(&mqtt, "sensors/");
Adafruit_MQTT_Subscribe motors = Adafruit_MQTT_Subscribe(&mqtt, "axes/");
Adafruit_MQTT_Publish debug = Adafruit_MQTT_Publish(&mqtt, "debug/");

PID pid = PID(0.03, MAX_FORCE, MIN_DISTANCE, kp, kd, ki);

void setup()
{

  Serial.begin(9600); // NON ELIMINARE
  int i;
  Ethernet.init(A4);
  for (i = 0; i < NUM_SERVO; i++)
  {
    servo[i].attach(servoPin[i]);
    servo[i].writeMicroseconds(SERVO_OFF);
  }
  Ethernet.begin(mac, addr); // start the Ethernet connection
  delay(ESC_DELAY);          // delay to allow the ESC to recognize the stopped signal
  mqtt.subscribe(&motors);   // subscribe to the mqtt topic "axes/"
  mqtt.subscribe(&sensors);  // subscribe to the mqtt topic "sensors/"
  Serial.println("Fine setup");
}

void loop()
{
  MQTT_connect(); // connect to the mqtt server
  while ((subscription = mqtt.readSubscription(MQTT_TIMEOUT)))
  {
    if (subscription == &sensors)
    {
      dim = strlen((char *)sensors.lastread);     // read the lenght of the recived data
      char cmd[dim + 1];                          // allocate a string to hold the read json string
      memcpy(cmd, (char *)sensors.lastread, dim); // copy the json string into a variable
      cmd[dim] = '\0';
      sensorsIn = JSON.parse(cmd); // parse the json file

      if (JSON.typeof(sensorsIn) == "undefined")
      { // check whether the command is correct
        continue;
      }

      if (sensorsIn.hasOwnProperty("depth"))
      {
        // parse the values recived into the allocated variable
        depth = (sensorsIn["depth"]);
        depth = abs(depth);
        
      }
    }

    if (subscription == &motors)
    {
      // pid_control();
      dim = strlen((char *)motors.lastread);     // read the lenght of the recived data
      cmd = new char[dim + 1];                   // allocate a string to hold the read json string
      memcpy(cmd, (char *)motors.lastread, dim); // copy the json string into a variable
      cmd[dim] = '\0';
      commandsIn = JSON.parse(cmd); // parse the json file

      if (JSON.typeof(commandsIn) == "undefined")
      { // check whether the command is correct
        continue;
      }

      // parse the values recived into the allocated variable
      Z_U = ((int)commandsIn["Z_UP"]);
      Z_D = ((int)commandsIn["Z_DOWN"]);
      ROLL = ((int)commandsIn["SHOULDER"]);
      PITCH = ((int)commandsIn["PITCH"]);
      YAW = ((int)commandsIn["YAW"]);
      Y = ((int)commandsIn["Y"]);
      X = ((int)commandsIn["X"]);

      // dynamic memory cleanup
      delete[] cmd;

      // remap the recived values into a proper interval range, in order to process them
      Z_URemap = map(Z_U, MIN_INPUT_READING, MAX_INPUT_READING, SERVO_OFF, MAX_Z);
      Z_DRemap = map(Z_D, MIN_INPUT_READING, MAX_INPUT_READING, SERVO_OFF, MAX_Z);
      XRemap = map(X, MIN_INPUT_READING, MAX_INPUT_READING, MIN_MAPPED_VALUE, MAX_MAPPED_VALUE);
      YRemap = map(Y, MIN_INPUT_READING, MAX_INPUT_READING, MIN_MAPPED_VALUE, MAX_MAPPED_VALUE);
      // XRemap2 = 0.5 * sqrt(2 + XRemap*XRemap - YRemap*YRemap + 2*sqrt(2)*XRemap) - 0.5 * sqrt(2 + XRemap*XRemap - YRemap*YRemap - 2*sqrt(2)*XRemap);
      // YRemap2 = 0.5 * sqrt(2 - XRemap*XRemap + YRemap*YRemap + 2*sqrt(2)*Y) - 0.5 * sqrt(2 - XRemap*XRemap + YRemap*YRemap - 2*sqrt(2)*YRemap);

      // Motors directions driving

      // x-y axes
      xp = abs(XRemap - SERVO_OFF) / (MIN_MAPPED_VALUE - MAX_MAPPED_VALUE);
      yp = abs(YRemap - SERVO_OFF) / (MIN_MAPPED_VALUE - MAX_MAPPED_VALUE);

      valx1 = (3000 - XRemap) * (xp + 0.5 - yp);
      valy1 = YRemap * (yp + 0.5 - xp);
      valx2 = XRemap * (xp + 0.5 - yp);
      valy2 = (3000 - YRemap) * (yp + 0.5 - xp);

      // plan zone - diag
      YRemap2 = (float)(YRemap - SERVO_OFF);
      XRemap2 = (float)(XRemap - SERVO_OFF);
      if ((YRemap2 > (XRemap2 * 0.846) && YRemap2 < (XRemap2 * 1.182)) ||
          (YRemap2 > (XRemap2 * 1.182) && YRemap2 < (XRemap2 * 0.846)))
      {
        if (depth < 0.3)
        {
          pid_on = false;
        }else{
          pid_on = true;
        }
        servo[FDX].writeMicroseconds(SERVO_OFF);
        delay(DELAY_PWM);
        servo[FSX].writeMicroseconds((int)(valy2 + valx2));
        delay(DELAY_PWM);
        servo[RDX].writeMicroseconds((int)(valy2 + valx1));
        delay(DELAY_PWM);
        servo[RSX].writeMicroseconds(SERVO_OFF);
      }
      else if (YRemap2 > (XRemap2 * 0.846 * (-1)) && YRemap2 < (XRemap2 * 1.182 * (-1)) ||
               (YRemap2 > (XRemap2 * 1.182 * (-1)) && YRemap2 < (XRemap2 * 0.846 * (-1))))
      {
        if (depth < 0.3)
        {
          pid_on = false;
        }
        else
        {
          pid_on = true;
        }
        servo[FDX].writeMicroseconds((int)(valy1 + valx2));
        delay(DELAY_PWM);
        servo[FSX].writeMicroseconds(SERVO_OFF);
        delay(DELAY_PWM);
        servo[RDX].writeMicroseconds(SERVO_OFF);
        delay(DELAY_PWM);
        servo[RSX].writeMicroseconds((int)(valy2 + valx2));
        delay(DELAY_PWM);
      }
      else
      {
        if (depth < 0.3)
        {
          pid_on = false;
        }
        else
        {
          pid_on = true;
        }
        servo[FDX].writeMicroseconds((int)(valy1 + valx2));
        delay(DELAY_PWM);
        servo[FSX].writeMicroseconds((int)(valy2 + valx2));
        delay(DELAY_PWM);
        servo[RDX].writeMicroseconds((int)(valy2 + valx1));
        delay(DELAY_PWM);
        servo[RSX].writeMicroseconds((int)(valy2 + valx2));
        delay(DELAY_PWM);
      }
      // z axes
      if (Z_URemap >= Z_DRemap)
      {
        servo[UPFDX].writeMicroseconds(Z_URemap >= 1550 ? 3000 - Z_URemap : SERVO_OFF);
        delay(DELAY_PWM);
        servo[UPRSX].writeMicroseconds(Z_URemap >= 1550 ? 3000 - Z_URemap : SERVO_OFF);
        delay(DELAY_PWM);
        servo[UPRDX].writeMicroseconds(Z_URemap >= 1550 ? 3000 - Z_URemap : SERVO_OFF);
        delay(DELAY_PWM);
        servo[UPFSX].writeMicroseconds(Z_URemap >= 1550 ? 3000 - Z_URemap : SERVO_OFF);
        delay(DELAY_PWM);
        if (Z_URemap >= 1550)
        {
          setPoint = depth;
          pid_on = false;
        }
      }
      else
      {

        servo[UPRDX].writeMicroseconds(Z_DRemap >= 1550 ? Z_DRemap : SERVO_OFF);
        delay(DELAY_PWM);
        servo[UPFSX].writeMicroseconds(Z_DRemap >= 1550 ? Z_DRemap : SERVO_OFF);
        delay(DELAY_PWM);
        servo[UPFDX].writeMicroseconds(Z_DRemap >= 1550 ? Z_DRemap : SERVO_OFF);
        delay(DELAY_PWM);
        servo[UPRSX].writeMicroseconds(Z_DRemap >= 1550 ? Z_DRemap : SERVO_OFF);
        delay(DELAY_PWM);
        if (Z_DRemap >= 1550)
        {
          setPoint = depth;
          pid_on = false;
        }
      }
    }
//    pid_control();
  }
  pid_control();
}

// the following function is used in order to connect to mqtt server or reconnect to it
// in case the connection is lost:
// hence the function is called at the beginning of each iteration of the loop function
void MQTT_connect()
{
  Serial.println("MQTT connecting...");
  // Stop if already connected.
  if (mqtt.connected())
  {
    return;
  }

  while (mqtt.connect() != 0)
  {
    Serial.println("redo MQTT connect");
    // connect will return 0 for connected
    mqtt.disconnect();
    delay(MQTT_CONNECT_RETRY_DELAY);
  }
}

void pid_control()
{
  char packet[80];
  if (pid_on == true)
  {
    double force = pid.calculate(setPoint, depth);
    double kgf = map_to_kgf(force, MIN_FORCE);
    int pwm = lookup_pwm(kgf);
    double var = map_pwm(pwm);
    servo[UPFDX].writeMicroseconds(pwm);
    servo[UPRSX].writeMicroseconds(pwm);
    servo[UPRDX].writeMicroseconds(pwm);
    servo[UPFSX].writeMicroseconds(pwm);
    sprintf(packet,
            "{\"setPoint\":%s,\"pwm\":%s,\"depth\":%s,\"Z_Uremap\":%s,\"Z_DRemap\":%s}",
            String(setPoint).c_str(),
            String(pwm).c_str(),
            String(depth).c_str(),
            String(Z_URemap).c_str(),
            String(Z_DRemap).c_str());
    debug.publish(packet);
  }
}

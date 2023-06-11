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

#define kp_z 89.0
#define ki_z 0.25
#define kd_z 0.2

#define kp_pitch 137.46
#define ki_pitch 0.0045
#define kd_pitch 0.105

#define kp_roll 338.73
#define ki_roll 0
#define kd_roll 0.094

#define MAX_FORCE 80.0
#define MIN_FORCE 1.0
#define MIN_DISTANCE 0.001

#define MAX_SPEED 1.0
#define dt 0.03

double tcmThrust1 = 0;
double tcmThrust2 = 0;
double tcmThrust3 = 0;
double tcmThrust4 = 0;

#define map_pwm(X) X == 1500 ? 0.0 : ((X / (1900.0 + 1100.0)) * dt * MAX_SPEED * (X >= 1500 ? 1.0 : -1.0))

// definition of the function to connect/reconnect to the mqtt server
void MQTT_connect();
void pid_control();
void tcm();
void printAttitude(double ax, double ay, double az);
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
double setPoint = 1.0;
double ax, ay, az;
float roll = 0;
float pitch = 0;
// json parsing related variables
int dim;
char *cmd;
bool pid_on = false;
JSONVar commandsIn;
JSONVar sensorsIn;

// mqtt and communication related variables
EthernetClient ethClient;
Adafruit_MQTT_Subscribe *subscription;
Adafruit_MQTT_Client mqtt(&ethClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME);
Adafruit_MQTT_Subscribe sensors = Adafruit_MQTT_Subscribe(&mqtt, "sensors/");
Adafruit_MQTT_Subscribe motors = Adafruit_MQTT_Subscribe(&mqtt, "axes/");
Adafruit_MQTT_Publish attitude = Adafruit_MQTT_Publish(&mqtt, "attitude/");

PID pid_z = PID(0.03, MAX_FORCE, MIN_DISTANCE, kp_z, kd_z, ki_z);
PID pid_roll = PID(0.03, MAX_FORCE, MIN_DISTANCE, kp_roll, kd_roll, ki_roll);
PID pid_pitch = PID(0.03, MAX_FORCE, MIN_DISTANCE, kp_pitch, kd_pitch, ki_pitch);

void setup()
{
  Serial.begin(115200);
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
      }
      if (sensorsIn.hasOwnProperty("ax"))
      { // check axis in packet
        // parse the values recived into the allocated variable
        ax = (sensorsIn["ax"]);
        ay = (sensorsIn["ay"]);
        az = (sensorsIn["az"]);
        printAttitude(ax, ay, az);
      }
      // call the method to convert the imu data to degrees
      pid_control();
    }
    pid_control();
  }
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
  double forcePitch = pid_pitch.calculate(1.0, pitch);
  double forceRoll = pid_roll.calculate(1.0, roll);
  double force_Z = pid_z.calculate(setPoint, depth);

  tcmThrust1 = 0.25 * force_Z + 0.9568 * forceRoll + (-0.9568) * forcePitch;
  tcmThrust2 = 0.25 * force_Z + (-0.9568) * forceRoll + (-0.9568) * forcePitch;
  tcmThrust3 = 0.25 * force_Z + 0.9568 * forceRoll + 0.9568 * forcePitch;
  tcmThrust4 = 0.25 * force_Z + (-0.9568) * forceRoll + 0.9568 * forcePitch;

  double kgfT2 = map_to_kgf(tcmThrust1, MIN_FORCE);
  double kgfT3 = map_to_kgf(tcmThrust2, MIN_FORCE);
  double kgfT4 = map_to_kgf(tcmThrust3, MIN_FORCE);
  double kgfT1 = map_to_kgf(tcmThrust4, MIN_FORCE);

  // double kgf_Z = map_to_kgf(force_Z, MIN_FORCE);
  // int pwm = lookup_pwm(kgf_Z);
  int pwm1 = lookup_pwm(kgfT1);
  int pwm2 = lookup_pwm(kgfT2);
  int pwm3 = lookup_pwm(kgfT3);
  int pwm4 = lookup_pwm(kgfT4);
  double var1 = map_pwm(pwm1);
  double var2 = map_pwm(pwm2);
  double var3 = map_pwm(pwm3);
  double var4 = map_pwm(pwm4);
  servo[UPFDX].writeMicroseconds(pwm2);
  delay(DELAY_PWM);
  servo[UPRSX].writeMicroseconds(pwm1);
  delay(DELAY_PWM);
  servo[UPRDX].writeMicroseconds(pwm3);
  delay(DELAY_PWM);
  servo[UPFSX].writeMicroseconds(pwm4);
  delay(DELAY_PWM);
}

void printAttitude(double ax, double ay, double az) // method to obtain the position in radians
{
  char packet[40];
  roll = atan2(ay, az);
  pitch = atan2(-ax, sqrt(ay * ay + az * az));
  roll *= 180.0 / PI;
  pitch *= 180.0 / PI;
  /*
   sprintf(packet,
                              "{\"roll\":%s,\"pitch\":%s}",
                              String(roll *= 180.0 / PI).c_str(),
                              String(pitch *= 180.0 / PI).c_str());
  attitude.publish(packet);
  */
}

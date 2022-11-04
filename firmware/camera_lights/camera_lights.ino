#include <SPI.h>
#include <Ethernet.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Servo.h>

#define LED_PIN_1 3
#define LED_PIN_2 5

#define AIO_SERVER      "10.0.0.254"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "atmega_ligths"

// Enter a MAC address for your controller below.
byte mac[] = {
    0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x03};

EthernetClient client;
IPAddress ip_servo(10,0,0,4);
const int port = 1883;
Servo myservo;  // create servo object to control a servo
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME/*, AIO_KEY*/);
Adafruit_MQTT_Subscribe camera = Adafruit_MQTT_Subscribe(&mqtt, "servo/");

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 0.015 seconds...");
       mqtt.disconnect();
       delay(15);  // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}

void setup()
{
  pinMode(LED_PIN_1, OUTPUT); //Led pin
  pinMode(LED_PIN_2, OUTPUT);
  analogWrite(LED_PIN_1, 0);  //ligths off
  analogWrite(LED_PIN_2, 0);

  myservo.attach(6);  // attaches the servo on pin 9 to the servo object

  Ethernet.init(10); // SCSn pin
  delay(1000);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Ethernet.begin(mac, ip_servo);

  mqtt.subscribe(&camera);
}

void loop()
{
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &camera) {
      //Serial.print(F("Got: "));
      //Serial.println();
      int dim = strlen((char *)camera.lastread);
      char cmd[dim+1];
      memcpy(cmd, (char *)camera.lastread, dim);
      cmd[dim]='\0';
      Serial.println(cmd);
      String value(cmd);
      //myservo.attach(6);
      delay(50);
      val = value.toInt();
      Serial.print(val);
      myservo.write(val);                  // sets the servo position according to the scaled value
      delay(200);                           // waits for the servo to get there
      //myservo.detach();
    }
  }
  
  
  delay(20);
}

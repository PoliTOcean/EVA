#include <SPI.h>
#include <Ethernet.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define STEPS 400
#define pin_step 4
#define pin_dir 5
#define motorInterfaceType 1

#define AIO_SERVER      "10.0.0.254"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "atmega_arm"

// Create a new instance of the AccelStepper class:
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x06};
EthernetClient client;
//PubSubClient mqttClient(ethClient);
IPAddress ip_arm(10,0,0,6);

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME/*, AIO_KEY*/);
Adafruit_MQTT_Subscribe opennipper = Adafruit_MQTT_Subscribe(&mqtt, "commands/");

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

void setup() {
  // put your setup code here, to run once:
  //servo.attach(6);
  Ethernet.init(53); // SCSn pin
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(49, OUTPUT);
  pinMode(6, OUTPUT);
  // Set the maximum speed in steps per second:
  //stepper.setMaxSpeed(1000);
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);  //disable stepper

  // start the Ethernet connection:
  Ethernet.begin(mac, ip_arm);
  delay(1000);
  
  mqtt.subscribe(&opennipper);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  MQTT_connect();

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(15))) {
    if (subscription == &opennipper) {
      int dim = strlen((char *)opennipper.lastread);
      char cmd[dim+1];
      memcpy(cmd, (char *)opennipper.lastread, dim);
      cmd[dim]='\0';
      Serial.println(cmd);
      if(String(cmd) == "OPEN NIPPER"){
        digitalWrite(49, HIGH);
        analogWrite(6, 127);
      }
      else if(String(cmd) == "STOP NIPPER"){
        analogWrite(6, 0);
      }
      else if(String(cmd) == "CLOSE NIPPER"){
        digitalWrite(49, LOW);   //set direction for actuator
        analogWrite(6, 127);    //move actuator
      }
      break;
     }
     
  }

  delay(15);
}

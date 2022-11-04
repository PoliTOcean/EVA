#include <SPI.h>
#include <Ethernet.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include <Linduino.h>

#include <LT_I2CBus.h>
#include <LT_SMBus.h>
#include <LT_SMBusARA.h>
#include <LT_SMBusBase.h>
#include <LT_SMBusGroup.h>
#include <LT_SMBusNoPec.h>
#include <LT_SMBusPec.h>
#include <LT_Wire.h>

#include <LT_FaultLog.h>
#include <LT_PMBus.h>
#include <LT_PMBusDetect.h>
#include <LT_PMBusDevice.h>
#include <LT_PMBusMath.h>
#include <LT_PMBusRail.h>
#include <LT_PMBusSpeedTest.h>

 uint8_t address1 = 32 ;
 uint8_t address2 = 36 ;
 float temperature1;
 float Iout1;
 float Vin1;
 float Vout1;
 float Iin1;

 float temperature2;
 float Iout2;
 float Vin2;
 float Vout2;
 float Iin2;
 
static LT_SMBus *smbus = new LT_SMBusNoPec();
static LT_PMBus *pmbus = new LT_PMBus(smbus);

#define _12_V_PIN 4
#define AIO_SERVER      "10.0.0.254"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "atmega_power"

unsigned char power_on = 1;

// Enter a MAC address for your controller below.
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x05};

EthernetClient client;
IPAddress ip_power(10,0,0,5);

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME/*, AIO_KEY*/);

Adafruit_MQTT_Publish current_voltage = Adafruit_MQTT_Publish(&mqtt, "sensors/");
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

Adafruit_MQTT_Publish toggle12v = Adafruit_MQTT_Publish(&mqtt, "components/");
Adafruit_MQTT_Subscribe onoff12v = Adafruit_MQTT_Subscribe(&mqtt, "commands/");

void setup()
{
  pinMode(_12_V_PIN, OUTPUT); //Led pin
  digitalWrite(_12_V_PIN, HIGH);

  Ethernet.init(10); // SCSn pin

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet:");
  Ethernet.begin(mac, ip_power);
  delay(1000);

  /*mqttClient.setServer(server, port);
  if (mqttClient.connect("atmega_power"))
  {
    Serial.println("Connection has been established, well done");

    mqttClient.setCallback( subscribePower );

    //subscribe to a specific topic in order to receive those messages
    mqttClient.subscribe("commands/");
  }
  else
  {
    Serial.println("Looks like the server connection failed...");
  }*/
  mqtt.subscribe(&onoff12v);
}

char current_packet[40];
char voltage_packet[40];

void loop()
{
  /*if (mqttClient.connected()==false){
    //Serial.println("MQTT Broker connection is down");
    if (mqttClient.connect("atmega_power")) {
       //Serial.println("MQTT Broker Connection Restarted");
           mqttClient.setCallback( subscribePower );

    //subscribe to a specific topic in order to receive those messages
    mqttClient.subscribe("commands/");
    }
  }*/

  MQTT_connect();

  Iout1 = pmbus->readIout(address1, false);
  temperature1 = pmbus->readOtemp(address1);
  Vout1 = pmbus->readVout(address1, false);
  Iout2 = pmbus->readIout(address2, false);
  temperature2 = pmbus->readOtemp(address2);
  Vout2 = pmbus->readVout(address2, false);

  sprintf(current_packet, "{\"current\": %s}", String(Iout1 + Iout2).c_str());

  //mqttClient.publish("sensors/", current_packet);
  current_voltage.publish(current_packet);

  sprintf(voltage_packet, "{\"voltage\": %s}", String((Vout1 + Vout2)/2.0).c_str());

  //mqttClient.publish("sensors/", voltage_packet);
  current_voltage.publish(voltage_packet);
  
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &onoff12v) {
      //Serial.print(F("Got: "));
      //Serial.println();
      int dim = strlen((char *)onoff12v.lastread);
      char cmd[dim+1];
      memcpy(cmd, (char *)onoff12v.lastread, dim);
      cmd[dim]='\0';
      Serial.println(cmd);
      if (String(cmd) == "TOGGLE POWER")
      {
        if(!power_on){
          power_on = 1;
          digitalWrite(_12_V_PIN, HIGH);
          if (! toggle12v.publish("{\"power\": \"Enabled\"}")) {
            Serial.println(F("Failed"));
          } else {
            Serial.println(F("OK!"));
          }
        }
         else{
          power_on = 0;
          digitalWrite(_12_V_PIN, LOW); 
          if (! toggle12v.publish("{\"power\": \"Disabled\"}")) {
            Serial.println(F("Failed"));
          } else {
            Serial.println(F("OK!"));
          }
         }
      }
    }
  }
  
  delay(500);
}

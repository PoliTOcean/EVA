/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/*
* Please refer to each DYNAMIXEL eManual(http://emanual.robotis.com/docs/en/dxl/) for more information regarding Torque.
*/

#include <DynamixelShield.h>
#include <Dynamixel2Arduino.h>
#include <Ethernet.h>
#include <Arduino_JSON.h>
#include "Adafruit_MQTT_Client.h"

#define MQTT_TIMEOUT 30             // milliseconds
#define MQTT_CONNECT_RETRY_DELAY 15 // milliseconds
#define AIO_SERVER "10.0.0.254"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "arm_board"

typedef enum{DOWN = -1, STOP = 0, UP = 1} arm_direction;

const uint8_t DXL_ID = 1;
const float DXL_PROTOCOL_VERSION = 1.0;

DynamixelShield dxl;

//This namespace is required to use Control table item names
using namespace ControlTableItem;
#define pinUP  9
#define pinDOWN  8
bool up = false;
bool down = false;
bool lastMoviment = false;
int dim;
JSONVar commandsIn;

unsigned char mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x06};
IPAddress addr(10, 0, 0, 6);
EthernetClient ethClient;
Adafruit_MQTT_Subscribe *subscription;
Adafruit_MQTT_Client mqtt(&ethClient, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME);
Adafruit_MQTT_Subscribe commands = Adafruit_MQTT_Subscribe(&mqtt, "commands/");

arm_direction;

// definition of the function to connect/reconnect to the mqtt server
void MQTT_connect();

void setup() {
  // put your setup code here, to run once:
  pinMode(pinUP, INPUT);
  pinMode(pinDOWN, INPUT);
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(DXL_ID);
  dxl.setOperatingMode(1, OP_EXTENDED_POSITION);
  dxl.writeControlTableItem(CW_ANGLE_LIMIT, 1, 4095);
  dxl.writeControlTableItem(CCW_ANGLE_LIMIT, 1, 4095);

  Ethernet.init(53);
  Ethernet.begin(mac, addr);
  mqtt.subscribe(&commands);
   
}

void loop() {

  MQTT_connect();
  while((subscription = mqtt.readSubscription(MQTT_TIMEOUT))){
    dim = strlen((char *)commands.lastread); // read the lenght of the recived data
    char cmd[dim + 1]; // allocate a string to hold the read json string
    memcpy(cmd, (char *)commands.lastread, dim); // copy the json string into a variable
    cmd[dim] = '\0';
    commandsIn = JSON.parse(cmd); // parse the json file

    if (JSON.typeof(commandsIn) == "undefined")
    { // check whether the command is correct
      continue;
    }



  }
  
}

// the following function is used in order to connect to mqtt server or reconnect to it
// in case the connection is lost:
// hence the function is called at the beginning of each iteration of the loop function
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
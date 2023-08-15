# third_ROV_firmware_Arduino

# IP Mapping

* sensors: 10.0.0.2
* thrusters: 10.0.0.3
* camera_lights: 10.0.0.4
* power: 10.0.0.5
* arm: 10.0.0.10

* control_raspberry: 10.0.0.252
* control_jetson: 10.0.0.253
* eva_jetson: 10.0.0.254

# MAC Mapping

* sensors: 00:AA:BB:CC:DE:02
* camera_lights: 00:AA:BB:CC:DE:03
* thrusters: 00:AA:BB:CC:DE:04
* power: 00:AA:BB:CC:DE:05
* arm: 00:AA:BB:CC:DE:06

# Requirements

This Atmega firmware has only been tested on Arduino IDE 1.8.x. Arduino 2.x does not work well

The following additional boards URLs must be installed

* https://politocean.github.io/politocean_boards/package_politocean_index.json
* http://arduino.esp8266.com/stable/package_esp8266com_index.json

If there is a library inside the Arduino sketch directory it must be installed because it is custom modified!
The following libraries must be downloaded, unless specified, from the Arduino Library Manager

* sensors: "BlueRobotics MS5837 Library" by BlueRobotics, v1.1.1
* power: "Linduino", "LT_SMBus", "LT_PMBus", "UserInterface" (download from https://github.com/analogdevicesinc/Linduino/tree/master/LTSketchbook)
* ESP_dashboard: "WebSockets" by Markus Sattler, v2.4.0; "ArduinoOTA" by Jurai Andrassy, v1.0.9 (remember to set the board as "Generic ESP8266 Module" or there will be compilation errors)

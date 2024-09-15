/*
*********************************************************************************************************
*                            Code of the ESP32 attached to CS (ESPB)
*
* Filename: EspB.ino
* Version: 8.1.1
* Developers: Fachechi Gino Marco, Gullotta Salvatore
* Company: Team PoliTOcean @ Politecnico di Torino
* Arduino board package: esp32 by Espressif Systems, v2.0.17
*
* Description:
* The ESPB main loop is a broker driven by two buffers, USB and WiFi one, filled by two callbacks.
* When a command arrives from the CS, the code sends it to the FLOAT or 
* feedbacks the CS with the system state (that may be stale). 
* While doing the latter, the ESPB tries to send a dummy package:
* if sending fails, it also reports the loss of connection to the CS. Part of the feedback 
* to the CS is also the current activation state of the Auto Mode (AM), as it is on the FLOAT.
* When data arrives from the FLOAT, the ESPB updates the system state accordingly
* and forwards the data to the CS, as a real time feedback.
********************************************************************************************************* 
*/

/** INCLUDES **/
//                                            Description                                            | Version
//                                                                                                   |
#include <Arduino.h> // Library needed if you are compiling on VSC PlatformIO plugin                 |    /
#include <esp_now.h> // Esp_now library for WiFi connections establishing and management             |    /
#include <WiFi.h>    // Layer for proper initialization and setting of ESP32 WiFi module             |    /
#include <Wire.h>    // Library for I2C connection protocol interface, used by MS5837.h and RTClib.h |    /

/** DEFINES **/
#ifndef ESPB_INO
  #define ESPB_INO
#endif

#define INPUT_LEN   250 // Length of the input on the MAC layer 
#define BUFFER_SIZE 20  // Chosen size in bytes of the Serial software buffer: 
//                         longer command and status strings are strongly discouraged
//                         and the GUI running on the CS should be aware of this limit

/** I/O STRUCTS 
  Structs containing message and command for communication over MAC. 
  Must match the receiver (ESPA) structures.
  Necessary for esp_now library compliance.
**/
typedef struct input_message {
  char message[INPUT_LEN];
} input_message;

typedef struct output_message {
  uint8_t command = 0;
} output_message;

output_message output;
input_message  input;

/** LIBRARY VARIABLES **/
esp_now_peer_info_t peerInfo; // Object containing info about the MAC peer we want to connect with
// Esp_now constant for peer MAC address value. Replace with the MAC address of your receiver (ESPA) 
uint8_t broadcastAddress[] = {0x24, 0xDC, 0xC3, 0xA0, 0x3B, 0x38};

/** PROGRAM GLOBAL CONSTANTS **/
const uint16_t MAX_CONN_TIME = 100; // Time in ms that has to elapse before send_message function stops to try a sending

/** PROGRAM GLOBAL VARIABLES **/
uint8_t auto_mode_active = 0;     // 1 if AM is active, 0 otherwise
uint8_t serial_rdy       = 0;     // Flag for signaling that the Serial software buffer serialInput is full and ready to be consumed
uint8_t message_rdy      = 0;     // Flag for signaling that a new message arrived on the MAC layer and is ready to be read 
int8_t  send_result      = -1;    // Flag for sending-over-MAC logic, needed to handle sending failure
int8_t  status           = 0;     // State variable that is updated according to arriving messages and is used to feedback the CS when requested
char    serialInput[BUFFER_SIZE]; // Serial software buffer used to empty the hardware one as soon as a new command arrives

/** PROGRAM LOCAL FUNCTIONS **/
/*
*********************************************************************************************************
*                                          OnDataRecv()
*
* Description : Callback for data arrival on the MAC layer: receives and manages the messages.
*               If the message_rdy flag is 0, the callback updates the message in the input data struct 
*               with the incoming message and sets the flag. The flag will be reset to 0 after 
*               the message has been consumed. Meanwhile no other incoming message will be accepted.
*
* Argument(s) : mac          : MAC address of the peer from which the data was received.
*
*               incomingData : Struct containing incoming data. Data maximum length is 250 bytes.
*
*               len          : Length of the received data.
*
* Return(s)   : none
*********************************************************************************************************
*/
void OnDataRecv (const uint8_t * mac, const uint8_t * incomingData, int len) {

  if (!message_rdy) {
    message_rdy = 1;
    memcpy(&input, incomingData, sizeof(input));
  }

}

/*
*********************************************************************************************************
*                                          OnDataSent()
*
* Description : Callback for data sending on the MAC layer: it updates send_result flag to 
*               inform other logics whether the sending of the last package went well or not. 
*               The flag has to be cleared to -1 before each sending.
*
* Argument(s) : mac    : MAC address of the peer to which the data was sended.
*
*               status : Status of the sending. It evaluates to ESP_NOW_SEND_SUCCESS if it succeeded.
*
* Return(s)   : none
*********************************************************************************************************
*/
void OnDataSent (const uint8_t * mac, esp_now_send_status_t status) {

  if (status == ESP_NOW_SEND_SUCCESS) send_result = 1; // If sending succeeds sets the flag to 1
  else send_result = 0;                                // Otherwise sets it to 0

}

/*
*********************************************************************************************************
*                                          send_command()
*
* Description : Function for command sending over the MAC layer: target peer is set during setup and 
*               should be the FLOAT (ESPA). In case of sending failure, signalled by the send_result flag, 
*               the message is continously sended until it succeeds or 
*               the max_conn_time milliseconds elapse.
*
* Argument(s) : message_str   : Char array containing the command code.
*
*               max_conn_time : Time that has to elapse before stopping to try the sending. 
*                               Expressed in milliseconds. 
*
* Return(s)   : 1 if sending succeeded, 0 if given time elapsed.
*********************************************************************************************************
*/
uint8_t send_command (uint8_t cmd_code, uint16_t max_conn_time) {
  output.command = cmd_code;                                             // Command code is copied in the output data struct
  uint64_t prec_time = millis();                                         // A time reference (ms elapsed from startup) is stored in prec_time
  while (true) {                                                         // [* sending sequence start]
    send_result = -1;                                                    // send_result flat is cleared
    esp_now_send(broadcastAddress, (uint8_t *) &output, sizeof(output)); // Tries to send the code over MAC layer
    while(send_result == -1);                                            // Waits for OnDataSent callback to set send_result flag
    if (send_result) return 1;                                           // If sending succeeds, function returns 1
    else if (millis() - prec_time > max_conn_time) return 0;             // If sending failed and max_conn_time milliseconds elapsed from time
  }//                                                                       reference set, the function returns 0. Otherwise it starts 
//                                                                          again the sending sequence from [* sending sequence start]
} 

/*
*********************************************************************************************************
*                                          serial_handler()
*
* Description : Callback function for Serial buffer management. If serialInput has already 
*               been consumed, when new data arrives on the Serial channel, the function
*               takes up to 20 bytes from the hardware buffer, stopping at the new line
*               character, copies them into the serialInput char array and fills the rest with 
*               string terminators. It also signals that the serialInput buffer is now ready to be 
*               read by setting the serial_rdy flag, that will be cleared only after serialInput
*               consumption. Meanwhile all new data arrivals on Serial channel will be ignored.
*               The function should grant a certain level of reliability in case of multiple, 
*               chained data arrivals, but remember that if the hardware buffer is full the new 
*               data arrival will be lost on the channel. Moreover, a too high arrival rate
*               can lead to command losses even on the software side.
*
* Argument(s) : none 
*
* Return(s)   : none
*********************************************************************************************************
*/
void serial_handler() {
  if (!serial_rdy) {                                                   // Checks if the flag is clear, hence serialInput is ready to be filled
    serial_rdy = 1;                                                    // Sets the serial_rdy flag, creating a lock on the serialInput array

    uint8_t buffer_index = 0;                                          
    char c = Serial.read();

    while (c != '\n' && Serial.available()) {                          // While bytes are available on the channel and its not a new line
      serialInput[buffer_index++] = c;                                 // Empties the harware buffer into the serialInput buffer
      c = Serial.read();
    }
    for(int i=buffer_index; i<BUFFER_SIZE; i++) serialInput[i] = '\0'; // Fill the rest of the array with string terminators
  }
}

/** SETUP **/ 
void setup() {
  Serial.begin(115200);                                                // Inits Serial Monitor
  Serial.onReceive(serial_handler);                                    // Sets callback for Serial channel data arrival

  WiFi.mode(WIFI_STA);                                                 // Sets device as a Wi-Fi Station

  if (esp_now_init() != ESP_OK) {                                      // Inits esp_now
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);                                // Registers esp_now arrival callback
  esp_now_register_send_cb(OnDataSent);                                // Registers esp_now sending callback
  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);                     // Registers peer by passing peer object pointer
  peerInfo.channel = 0;                                                // Channel selection
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){                          // Adds peer
    Serial.println("Failed to add peer");
    return;
  }
}

/** BROKER **/
void loop() {
  if (message_rdy) {                                                                         // Checks if there's any message ready to be read
    // Updates the status whit respect to the relative ack
         if (strcmp(input.message, "FLOAT_IDLE")        == 0) status = 0;                    // The FLOAT is in idle with no data to send
    else if (strcmp(input.message, "FLOAT_IDLE_W_DATA") == 0) status = 1;                    // The FLOAT is in idle and has some data to send
    else status = 2;                                                                         // If it's not in idle, the FLOAT is executing a command
    
    Serial.println(input.message);                                                           // Sends incoming message on Serial channel 
//                                                                                              for real time feedback to the CS
    if (strcmp(input.message, "SWITCH_AM_RECVD") == 0) auto_mode_active = !auto_mode_active; // If AM toggle command succeeded,
//                                                                                              toggles flag for feedback purposes
    message_rdy = 0;                                                                         // Releases the lock on the message container
  }

  if (serial_rdy) {                            // Checks if there's any command ready to be consumed 
    uint8_t result;
    // Broker that sends different command codes to the FLOAT according to the incoming command string:
    // CS has to be aware of this command strings, as well as the FLOAT should be able to bind different 
    // codes to the right command. Exception is the "STATUS" command string that expects a feedback to the
    // CS about the status of the system 
    if      (strcmp(serialInput, "GO"               ) == 0) send_command(1, MAX_CONN_TIME);
    else if (strcmp(serialInput, "LISTENING"        ) == 0) send_command(2, MAX_CONN_TIME);
    else if (strcmp(serialInput, "BALANCE"          ) == 0) send_command(3, MAX_CONN_TIME);
    else if (strcmp(serialInput, "CLEAR_SD"         ) == 0) send_command(4, MAX_CONN_TIME);
    else if (strcmp(serialInput, "SWITCH_AUTO_MODE" ) == 0) send_command(5, MAX_CONN_TIME);
    else if (strcmp(serialInput, "SEND_PACKAGE"     ) == 0) send_command(6, MAX_CONN_TIME);
    else if (strcmp(serialInput, "TRY_UPLOAD"       ) == 0) send_command(7, MAX_CONN_TIME);
    else if (strcmp(serialInput, "STATUS"           ) == 0) {
      // status driven switch that sends a status string to the CS if requested
      switch (status) { 
        case 0:
          Serial.print("CONNECTED");
          break;
        case 1:
          Serial.print("CONNECTED_W_DATA");
          break;
        case 2:
          Serial.print("EXECUTING_CMD");
          break;
        default: 
          Serial.print("STATUS_ERROR");
          break;
      }
      // Additional info to the status string, including current AM activation state and current WiFi connection state.
      // AM activation flag is updated toghether with the actual one on the FLOAT
      Serial.print(" | ");
      if (auto_mode_active) Serial.print("AUTO_MODE_YES"); 
      else                  Serial.print("AUTO_MODE_NO");

      result = send_command(0, MAX_CONN_TIME); // Sends a dummy package (command code 0) to the FLOAT to detect connection state
      Serial.print(" | ");
      if (result) Serial.println("CONN_OK");
      else        Serial.println("CONN_LOST");
    }

    serial_rdy = 0;                            // Releases the lock on the command container
  }
}

/*TASK 3 DESCRIPTION
 * 
 * 1 - COMMUNICATION WITH THE WORKING STATION PRIOR DESCENDING (10 PTS)
 * 
 * 2 - FIRST DESCENDING -> WE SEND A COMMAND SIGNAL TO THE ESP THAT STARTS THE DESCENDING (10 PTS)
 * 
 * 3 - COME BACK TO THE SURFACE AND SEND DATA AGAIN (10 PTS)
 * 
 * 4 - SECOND DESCENDING -> WE SEND ANOTHER SIGNAL TO THE ESP THAT START THE DESCENDING (15 PTS)
 * 
 * 5 - COME BACK TO THE SURFACE AND SEND DATA AGAIN (10 PTS)
 * 
 */
#include <DynamixelPolitocean.h>
#include <string.h>
#include "RTClib.h"

void printTime();
void goUp();
void goDown();
String cmd;
RTC_PCF8523 rtc; 
DynamixelPolitocean dxl(Wire,0x4D, 1); 
DateTime now = rtc.now();

#define DESCENDING_TIME 10000 //ms to complete a full descend -> GO DOWN
#define ASCENDING_TIME 10000  //ms to complete a full ascend  -> GO UP
void setup() { 
  
  Serial.begin(57600); 
  //Serial.println("here");
 
  delay(100); 
  dxl.begin(57600); 
  delay(100); 
  dxl.setOperatingMode(WHEEL); 

   while(!rtc.begin()) { 
    Serial.println("RTC NOT WORKING"); 
    delay(200);
  } 
 
  if (rtc.lostPower()) { 
    //enter if the status registers says that a power loss has occurred, NECESSARY
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  } 
  
} 
 
void loop() { 

/*
 *  LOOP DISPLAYING TIME AND ID, ONCE EVERY SECOND
 *  UNTIL THE COMMAND "GO" HAS BEEN SENT TO THE ESP -> THIS STOP THE TRANSMISSION AND THEN PROCEEDS WITH THE DESCENDING, THEN CONTINUE TO SEND DATA
 */

 //FIRST PRINT OUR ID
 Serial.print("EX04");

 //NOW PRINT THE TIME
 printTime();   //print the data to the esp monitorà
 delay(1000);


 //CHECKING IF DESCENDING COMMAND IS READY
 if(Serial.available() != 0)
 {
    cmd = Serial.readString();  //RECEIVED COMMAND

    if(cmd == "GO")   //DECODE SIGNAL
    {
      //DESCENDING
      goDown();
      delay(DESCENDING_TIME);

      //ASCENDING
      goUp();
      delay(ASCENDING_TIME);      
    }
 }
  
}

void printTime()
{
  //this function only prints the time (AS SPECIFIED BY THE MATE ROV - TASK 3)
  DateTime now = rtc.now();
  
  Serial.print(now.year(), DEC); 
  Serial.print("/"); 
  Serial.print(now.month(), DEC); 
  Serial.print("/"); 
  Serial.print(now.day(), DEC); 
  Serial.print(" "); 
  Serial.print(now.hour(), DEC); 
  Serial.print(':'); 
  Serial.print(now.minute(), DEC); 
  Serial.print(':'); 
  Serial.print(now.second(), DEC); 
  Serial.println();
}

void goUp()
{
  //GOING UP -> ROTATE CCW
  dxl.setVelocityWheelMode(1023, CCW);
}

void goDown()
{
  //GOING DOWN -> ROTATE CW
  dxl.setVelocityWheelMode(1023, CW);
}

  
#include <DynamixelPolitocean.h>
#include <string.h>
#include "RTClib.h"


RTC_PCF8523 rtc; 
DynamixelPolitocean dxl(Wire,0x4D, 1); 
void setup() { 
  
  Serial.begin(9600); 
  //Serial.println("here");
 
  delay(100); 
  dxl.begin(57600); 
  delay(100); 
  dxl.setOperatingMode(WHEEL); 
  //dxl.TorqueOn(); 
  //dxl.setVelocity(1023);

   while(!rtc.begin()) { 
    Serial.println("verifica connessioni"); 
    //while(true);
    delay(200);
  } 
 
  if (rtc.lostPower()) { 
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  } 
  
} 
 
void loop() { 
//Serial.println("here_loop");
// delay(4000); 
//  dxl.setVelocityWheelMode(1023, CW);
//  delay(2000);
//  dxl.setVelocityWheelMode(1000,CCW);
//  delay(2000);
   
  DateTime now = rtc.now(); 
  dxl.LedOn();
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
  delay(2000);
  //dxl.setVelocityWheelMode(1023, CCW);
  now = rtc.now(); 
  dxl.LedOff();
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
  delay(2000);

//  DateTime now = rtc.now(); 
// 
//  Serial.print(now.year(), DEC); 
//  Serial.print("/"); 
//  Serial.print(now.month(), DEC); 
//  Serial.print("/"); 
//  Serial.print(now.day(), DEC); 
//  Serial.print(" "); 
//  Serial.print(now.hour(), DEC); 
//  Serial.print(':'); 
//  Serial.print(now.minute(), DEC); 
//  Serial.print(':'); 
//  Serial.print(now.second(), DEC); 
//  Serial.println(); 
 

  
  
 
}

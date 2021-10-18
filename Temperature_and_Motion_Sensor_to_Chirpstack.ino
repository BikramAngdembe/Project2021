#include <Wire.h>
#include "AHT20.h"
AHT20 AHT;

int LED = 13;
int PIR_MOTION_SENSOR = D2;
int pirState = LOW;

void setup() 
{
  pinMode(D2, INPUT);
  Serial.begin(9600);
  Serial2.begin(9600);
  AHT.begin();
  Serial2.println("AT+ID=DevEui, \"01f104a1d83e3fa8\"");
  Serial2.println("AT+ID=DevAddr, \"0166bcca\"");
  Serial2.println("AT+KEY=NWKSKEY, \"331e698de3015d78aa0977662b434d0f\"");
  Serial2.println("AT+KEY=APPSKEY, \"c53e1de903cabc89d997072a52adc4c5\"");
  Serial2.println("AT+DR=AU915");
  Serial2.println("AT+MODE=LWABP");
}

void loop() 
{
 
 while (Serial2.available()) 
 { 
    Serial.write(Serial2.read()); // read it and send it out Serial (USB)
 }

  float humi, temp;
 
  int ret = AHT.getSensor(&humi, &temp);
 
  if(ret)     // GET DATA OK
  {
    Serial2.print("AT+MSG=\"");
    Serial2.print(temp);
    Serial2.print(",");
    Serial2.print(humi);
    Serial2.println("\"");
    Serial.print("humidity: ");
    Serial.print(humi*100);
    Serial.print("%\t temerature: ");
    Serial.println(temp);
   }
    else        // GET DATA FAIL
    {
      Serial.println("GET DATA FROM AHT20 FAIL");
    }
    delay(6000);
   
  int sensorValue = digitalRead(PIR_MOTION_SENSOR);
    
  if (sensorValue == HIGH) {
    digitalWrite(LED, HIGH);

    if (pirState == LOW) {
      Serial2.println("AT+MSG=\"Motion Detected\"");
      Serial.println("Motion Detected!");
      pirState = HIGH;
    }
    delay(4000);
  }else{
    digitalWrite(LED, LOW);

    if(pirState == HIGH){
      Serial2.println("AT+MSG=\"Motion Ended\"");
      Serial.println("Motion Ended!");
      pirState = LOW;
      }
      delay(4000);
    }
}

#include <Wire.h>
#include "AHT20.h"
AHT20 AHT;

int led = 13;
int value = 0;
int pirState = LOW;

void setup() {
  pinMode(D2, INPUT);
  Serial.begin(115200);
  AHT.begin();
}

void loop() {

  value = digitalRead(D2);
  float humi, temp;
  int ret = AHT.getSensor(&humi, &temp);
  
  if(ret)
  {
    Serial.print("humidity: ");
        Serial.print(humi*100);
        Serial.print("%\t temerature: ");
        Serial.println(temp);
        delay(100);
    }
    else        // GET DATA FAIL
    {
        Serial.println("GET DATA FROM AHT20 FAIL");
    }
  if (value == HIGH) {
    digitalWrite(led, HIGH);

    if (pirState == LOW) {
      Serial.println("Motion Detected!");
      pirState = HIGH;
    }
  }else{
    digitalWrite(led, LOW);

    if(pirState == HIGH){
      Serial.println("Motion Ended!");
      pirState = LOW;
      }
    }
}

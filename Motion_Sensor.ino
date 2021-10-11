int led = 13;
int value = 0;
int pirState = LOW;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(D2, INPUT);
  Serial.begin(9600);
}

void loop() {

  value = digitalRead(D2);

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

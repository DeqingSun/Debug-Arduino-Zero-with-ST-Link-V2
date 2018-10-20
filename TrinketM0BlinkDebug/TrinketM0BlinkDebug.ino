#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  volatile int a=0;
  a=1;
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(1000);
  a=0;  
  digitalWrite(LED_BUILTIN, LOW); 
  delay(1000);
  Serial.println("TEST");
}

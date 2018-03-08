#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  volatile int a=0;
  a=1;
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(100);
  a=0;  
  digitalWrite(LED_BUILTIN, LOW); 
  delay(100);
}

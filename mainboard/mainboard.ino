#include "pins.h"
#include "startup.c"

void setup() 
{
  init_gpio();
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
}

void loop() 
{
  digitalWrite(PIN_STAT1,HIGH);
  digitalWrite(PIN_STAT0,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(A4,LOW);
  digitalWrite(A5,LOW);
  //digitalWrite(PIN_STAT1,!digitalRead(PIN_STAT1));
  //digitalWrite(PIN_STAT0,!digitalRead(PIN_STAT1));
  //delay(250);
}

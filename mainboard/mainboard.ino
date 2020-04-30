#include "pins.h"
#include "startup.hpp"
#include "gpio.hpp"
#include <Wire.h>

void setup() 
{
  init_gpio();
  Wire.begin(); // join i2c bus as master
  Serial.begin(115200);
  Serial.setTimeout(50);
  pinMode(PIN_GRIND,OUTPUT);
}

void loop() 
{
  digitalWrite(PIN_H1,HIGH);
  digitalWrite(PIN_GRIND,HIGH);
  if (Serial.available())
  {
    uint8_t msg = Serial.readString().toInt();
    Wire.beginTransmission(0x10);
    Wire.write(msg);
    Wire.endTransmission();
  }
  Serial.print(millis());
  Serial.print('\t');
  Serial.print(32+9.0*get_tz(PIN_TZ1)/5.0);
  Serial.print('\t');
  Serial.print(analogRead(PIN_TZ1));
  Serial.print('\t');
  Serial.print(32+9.0*get_tz(PIN_TZ2)/5.0);
  Serial.print('\t');
  Serial.print(analogRead(PIN_TZ2));
  Serial.print('\t');
  Serial.print(32+9.0*get_tz(PIN_TZ3)/5.0);
  Serial.print('\t');
  Serial.print(analogRead(PIN_TZ3));
  Serial.print('\t');
  Serial.print(32+9.0*get_tz(PIN_TZ4)/5.0);
  Serial.print('\t');
  Serial.println(analogRead(PIN_TZ4));
}

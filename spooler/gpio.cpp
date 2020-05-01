#include "gpio.hpp"
#include "pins.h"


void gpio_init()
{
  pinMode(PIN_SERVO,OUTPUT);
  pinMode(PIN_MSPIN,OUTPUT);
  
  pinMode(PIN_D2,OUTPUT);
  pinMode(PIN_D5,OUTPUT);
  
  pinMode(PIN_ENC_A,INPUT);
  pinMode(PIN_ENC_B,INPUT);
  
  pinMode(PIN_24VFB,INPUT);
}


float get_24vfb()
{
  return (analogRead(PIN_24VFB)/1024.0)*MAX_24VFB;
}


void write_motor(float pct)
{
  analogWrite(PIN_MSPIN,255*min(1,max(0)))
}

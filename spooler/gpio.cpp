#include "gpio.hpp"
#include "pins.h"

volatile long encoder_delta = 0;
void gpio_init()
{
  pinMode(PIN_SERVO,OUTPUT);
  pinMode(PIN_MSPIN,OUTPUT);
  
  pinMode(PIN_D2,OUTPUT);
  pinMode(PIN_D5,OUTPUT);
  
  pinMode(PIN_ENC_A,INPUT);
  pinMode(PIN_ENC_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(PIN_ENC_A),isr_enc_a,CHANGE);
  
  pinMode(PIN_24VFB,INPUT);
}


float get_24vfb()
{
  return (analogRead(PIN_24VFB)/1024.0)*MAX_24VFB;
}


void write_motor(float pct)
{
  analogWrite(PIN_MSPIN,255*min(1,max(0,pct)));
}

void isr_enc_a()
{
  encoder_delta += 1-2*(digitalRead(PIN_ENC_A) xor digitalRead(PIN_ENC_B));
}

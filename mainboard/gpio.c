#ifndef GPIO_C
#define GPIO_C

#include "pins.h"
// The thermal probes are a resistance of 100kohm at 25 degrees C, with a B value of 3950.

float get_tz1()
{
  return ((293.15*3950)/(293.15*log((1024/digitalRead(PIN_TZ1)-1)/100)+3950))-273.15;
}

float get_tz2()
{
  return ((293.15*3950)/(293.15*log((1024/digitalRead(PIN_TZ2)-1)/100)+3950))-273.15;
}

float get_tz3()
{
  return ((293.15*3950)/(293.15*log((1024/digitalRead(PIN_TZ3)-1)/100)+3950))-273.15;
}

float get_tz4()
{
  return ((293.15*3950)/(293.15*log((1024/digitalRead(PIN_TZ4)-1)/100)+3950))-273.15;
}





#endif

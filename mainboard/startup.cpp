
#include "pins.h"

#include <Arduino.h>


void init_gpio()
{
  // IR Inputs For Distance Sensors
  pinMode(PIN_GRINDER_INTERLOCK_IR,INPUT);
  pinMode(PIN_EXTRUDER_IN_IR,INPUT);
  
  // AC Timing Signal Input
  pinMode(PIN_AC_TIMING,INPUT);
  
  // Encoder Inputs
  pinMode(PIN_ENCODER_A,INPUT);
  pinMode(PIN_ENCODER_B,INPUT);

  // Grinder and Extruder DC Motor LSD Control
  pinMode(PIN_GRIND,OUTPUT);
  digitalWrite(PIN_GRIND,LOW);
  pinMode(PIN_EXTRUDE,OUTPUT);
  digitalWrite(PIN_EXTRUDE,LOW);

  // AC Heater Control Outputs
  pinMode(PIN_H1,OUTPUT);
  digitalWrite(PIN_H1,LOW);
  pinMode(PIN_H2,OUTPUT);
  digitalWrite(PIN_H2,LOW);
  pinMode(PIN_H3,OUTPUT);
  digitalWrite(PIN_H3,LOW);

  // Thermal Zone Thermistors
  pinMode(PIN_TZ1,INPUT);
  pinMode(PIN_TZ2,INPUT);
  pinMode(PIN_TZ3,INPUT);
  pinMode(PIN_TZ4,INPUT);

  // Generic Status Lights
  pinMode(PIN_STAT1,OUTPUT);
  digitalWrite(PIN_STAT1,LOW);
  pinMode(PIN_STAT0,OUTPUT);
  digitalWrite(PIN_STAT0,LOW);
  
}

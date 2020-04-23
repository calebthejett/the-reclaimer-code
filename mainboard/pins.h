#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

// IR Inputs For Distance Sensors
#define PIN_GRINDER_INTERLOCK_IR  8
#define PIN_EXTRUDER_IN_IR        11

// AC Timing Signal Input
#define PIN_AC_TIMING             12

// Encoder Inputs
#define PIN_ENCODER_A             2
#define PIN_ENCODER_B             3

// Grinder and Extruder DC Motor LSD Control
#define PIN_GRIND                 6
#define PIN_EXTRUDE               7

// AC Heater Control Outputs
#define PIN_H1                    13
#define PIN_H2                    4
#define PIN_H3                    5

// Thermal Zone Thermistors
#define PIN_TZ1                   A2
#define PIN_TZ2                   A3
#define PIN_TZ3                   A6
#define PIN_TZ4                   A7

// Generic Test Point
#define PIN_TP5                   A1

// Generic Status Lights
#define PIN_STAT1                 9
#define PIN_STAT0                 10

#endif

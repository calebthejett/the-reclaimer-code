#ifndef PINS_H
#define PINS_H

// IR Inputs For Distance Sensors
#define PIN_GRINDER_INTERLOCK_IR  D8
#define PIN_EXTRUDER_IN_IR        D11

// AC Timing Signal Input
#define PIN_AC_TIMING             D12

// Encoder Inputs
#define PIN_ENCODER_A             D2
#define PIN_ENCODER_B             D3

// Grinder and DC Motor LSD Control
#define PIN_GRIND                 D6
#define PIN_EXTRUDE               D7

// AC Heater Control Outputs
#define PIN_H1                    D13
#define PIN_H2                    D4
#define PIN_H3                    D5

// Thermal Zone Thermistors
#define PIN_TZ1                   A2
#define PIN_TZ2                   A3
#define PIN_TZ3                   A6
#define PIN_TZ4                   A7

// Generic Test Point
#define PIN_TP5                   A1

// Generic Status Lights
#define PIN_STAT1                 D9
#define PIN_STAT0                 D10

#endif

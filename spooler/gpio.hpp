#ifndef GPIO_HPP
#define GPIO_HPP

#define MAX_24VFB 34.133

#include <Arduino.h>

extern bool running;
extern uint8_t status;
extern float motor_speed;
extern float servo_angle;
extern float spool_speed;
extern float spool_id;
extern float spool_od;
extern float spool_height;

void init_gpio();

float get_24vfb();

void write_motor(float pct);

void isr_enc_a();

void calculate();

void run();

void reset();

#endif

#include "common.hpp"
#include "gpio.hpp"
#include "pins.h"
#include "i2c.hpp"

uint8_t status = STAT_OK;
float motor_speed = 0;
float servo_angle = 0;
float spool_speed = 0;
float spool_id = 0;
float spool_od = 0;
float spool_height = 0;
bool running = false;

void setup() 
{
  init_i2c();
  init_gpio();
}

void loop() 
{
  proc_i2c();
  run();
}

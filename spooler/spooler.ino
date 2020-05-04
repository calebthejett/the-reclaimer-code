#include "common.hpp"
#include "gpio.hpp"
#include "pins.h"
#include "i2c.hpp"
#include "scheduler.hpp"

#define SCHEDULER_DEBUG

uint8_t status = STAT_OK;
float motor_speed = 0;
float servo_angle = 90;
float spool_speed = 0;
float spool_id = 0;
float spool_od = 0;
float spool_height = 0;
bool running = false;

Scheduler scheduler;
void setup() 
{
  init_i2c();
  init_gpio();
  Serial.begin(115200);
  scheduler.add_task(proc_i2c,5000,100);
  scheduler.add_task(calculate,20000,2000);
  scheduler.add_task(run,30000,2000);
}

void loop() 
{
  uint8_t task = scheduler.least_slack_time();
#ifdef SCHEDULER_DEBUG
  scheduler.run_task(task,true);
#else
  scheduler.run_task(task,false);
#endif
}

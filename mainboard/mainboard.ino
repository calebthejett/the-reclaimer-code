#include "pins.h"
#include "startup.hpp"
#include "gpio.hpp"
#include "i2c.hpp"

#include <Wire.h>

#include "scheduler.hpp"
Scheduler scheduler;

void setup() 
{
  init_gpio();
  init_i2c();
  Serial.begin(115200);
  scheduler.add_task(proc_i2c,10000,2000);
  scheduler.add_task(handle_h1,500000,2000);
  scheduler.add_task(handle_h2,500000,2000);
  scheduler.add_task(handle_h3,500000,2000);
  scheduler.add_task(handle_grinder,100000,10000);
  scheduler.add_task(handle_extruder,100000,10000);
}

#define SCHEDULER_DEBUG

void loop() 
{
  uint8_t task = scheduler.least_slack_time();
#ifdef SCHEDULER_DEBUG
  scheduler.run_task(task,true);
#else
  scheduler.run_task(task,false);
#endif
}

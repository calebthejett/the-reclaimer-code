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
#if defined(DEBUG) || defined(SCHEDULER_DEBUG)
  Serial.begin(115200);
#endif
  scheduler.add_task(proc_i2c,3000,100);
  scheduler.add_task(calculate,5000,2000);
  scheduler.add_task(run,5000,2000);
}

void loop() 
{
  uint8_t task = scheduler.shortest_response_time();
  long slack_time = scheduler.run_task(task);
  static long last_time = micros();
  static long print_delay = 0;
  last_time = micros();
#ifdef SCHEDULER_DEBUG
  Serial.print(last_time);
  Serial.print("\t");
  Serial.print(task);
  Serial.print("\t");
  Serial.println(slack_time+print_delay);
#endif
  if (slack_time+print_delay < 0)
  {
    digitalWrite(PIN_D5,HIGH);
  }
  print_delay = micros()-last_time;
}

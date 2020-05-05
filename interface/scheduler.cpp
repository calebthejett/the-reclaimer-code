#include "scheduler.hpp"


void noop() {__asm__("nop\n\t");}; //exec assembly no-op function

uint8_t Scheduler::round_robin()
{
  static uint8_t last_task = 0;
  last_task++;
  if(last_task == num_tasks)
  {
    last_task = 0;
  }
  return last_task;
}

uint8_t Scheduler::least_slack_time()
{
  uint8_t chosen_task = 0;
  long chosen_srt = 2147483646; //max out the long
  for(int i = 0; i < num_tasks; i++)
  {
    long srt = next_deadline[i]-time_required[i];
    if (srt< chosen_srt)
    {
      chosen_srt = srt;
      chosen_task = i;
    }
  }
  return chosen_task;
  
}

uint8_t Scheduler::earliest_deadline_first()
{
  uint8_t chosen_task = 0;
  long chosen_deadline = 2147483646; //max out the long
  for(int i = 0; i < num_tasks; i++)
  {
    if (next_deadline[i] < chosen_deadline)
    {
      chosen_deadline = next_deadline[i];
      chosen_task = i;
    }
  }
  return chosen_task;
}

uint8_t Scheduler::add_task( fp task, long deadline, long time_req)
{
  if (num_tasks < MAX_TASKS)
  {
    long now = micros();
    tasks[num_tasks] = task;
    deadlines[num_tasks] = deadline;
    next_deadline[num_tasks] = now+deadline;
    time_required[num_tasks] = time_req;
    last_run[num_tasks] = 0;
    num_tasks++;
    return num_tasks-1;
  }
  else
  {
    return 0xFF;
  }
}

void Scheduler::remove_task(uint8_t task)
{
  if (task < num_tasks)
  {
    for(int i = task; i < num_tasks; i++)
    {
      if (i < (num_tasks-1))
      {
        tasks[i] = tasks[i+1];
        deadlines[i] = deadlines[i+1];
        next_deadline[i] = next_deadline[i+1];
        time_required[i] = time_required[i+1];
      }
      num_tasks --;
    }
  }
}

void Scheduler::run_task(uint8_t task, bool readout)
{
  long start = micros();
  tasks[task]();
  long finish = micros();
  if (readout)
  {
    Serial.print(task); //what task ran
    Serial.print(",");
    Serial.print(last_run[task]); //what time it arrived
    Serial.print(",");
    Serial.print(start); //what time it started
    Serial.print(",");
    Serial.print(finish); //what time it finished
    Serial.print(",");
    Serial.println(next_deadline[task]); //what time it needed to finish by
  }
  time_required[task] = micros()-start;
  next_deadline[task] = finish+deadlines[task];
  last_run[task] = finish;
}

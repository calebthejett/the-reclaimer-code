#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <Arduino.h>

#define MAX_TASKS 8


typedef void (*fp) (void);

void noop(); //exec assembly no-op function

class Scheduler
{
  private:
    uint8_t num_tasks = 0;
    fp tasks[MAX_TASKS];
    //all times in microseconds
    long deadlines[MAX_TASKS];
    long next_deadline[MAX_TASKS];
    long time_required[MAX_TASKS];
    long last_run[MAX_TASKS];
    
  public:

    uint8_t round_robin();
    uint8_t least_slack_time();
    uint8_t earliest_deadline_first();
    uint8_t add_task( fp task, long deadline, long time_required);
    void remove_task(uint8_t task);

    void run_task(uint8_t task, bool readout);
};

#endif

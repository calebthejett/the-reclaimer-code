#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <LiquidCrystal.h>
#include "pins.h"
#include "common.hpp"

#define MAX_ENTRIES 8


void start_lcd();


class Menu
{
  public:
    virtual bool handle(){};
    virtual void make_first_time(){};
};

class Setting : public Menu
{
  private:
    const char * caption;
    bool first_time = true;
    uint8_t decimals;
    float * target_val;
    float new_val, min_val, max_val, delta_val;
    
  public:
    Setting(const char s_caption[], uint8_t s_decimals, float * s_target_val, float s_min_val, float s_max_val, float s_delta_val);
    bool handle();
    void make_first_time(){first_time = true;};
};

class List : public Menu
{
  private:
    const char * const * entries;
    Menu * targets[MAX_ENTRIES];
    bool in_submenu = false;
    int8_t selection = 0;
    int8_t * selected;
    int8_t last_selection = 0;
    int8_t num_entries;
    
  public:
    bool first_time = true;
    List(const char * const * const s_entries, Menu * s_targets[], int8_t s_num_entries, int8_t *s_selected);
    bool handle();
    void make_first_time(){first_time = true;};
};

class Action : public Menu
{
  private:
    fp_bool target;
    bool one_time;
  public:
    Action(fp_bool s_target, bool s_one_time=true);
    bool handle();
};

class Monitor : public Menu
{
 private:
    const char * caption;
    float * value;
    int interval;
  /*   
  public:
    List(String * s_entries, int8_t s_num_entries);
    bool handle();
    int8_t get_value();*/
  public:
    Monitor(const char * const s_caption, float * s_value, int interval_millis = 1000);
    bool first_time = true;
    bool handle();
    void make_first_time(){first_time = true;};
};


#endif

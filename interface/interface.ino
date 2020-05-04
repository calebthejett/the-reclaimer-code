#include <LiquidCrystal.h>
#include <Wire.h>
#include "i2c.hpp"
#include "pins.h"
#include "lcd_chars.h"
#include "display.hpp"
#include "encoder.hpp"
#include "scheduler.hpp"
//Set_value::Set_value(char *s_caption, uint8_t s_caption_len, uint8_t s_decimals, float s_original_val, float s_new_val, float s_min_val, float s_max_val, float s_delta_val);
//Set_value test = Set_value("test",4,2,42,69,-5,101,0.4);
extern bool button_pressed;
float h1 = 35;
float h2 = 35;
float h3 = 35;
float spool_ir = 25;
float spool_or = 80;
float spool_height = 40;
float speed = 200;

float tz1 = 0;
float tz2 = 0;
float tz3 = 0;
float tz4 = 0;
float v24 = 0;
float extrude_speed = 100;
byte spool_status = 0xFF;
byte main_status = 0xFF;

////////////////////////////////////////////////////////////////////

const char h1_set_txt[] PROGMEM = "Heater 1 (C)";
const char h2_set_txt[] PROGMEM = "Heater 2 (C)";
const char h3_set_txt[] PROGMEM = "Heater 3 (C)";
Setting h1_set = Setting(h1_set_txt, 0, &h1, 0, 250, 1);
Setting h2_set = Setting(h2_set_txt, 0, &h2, 0, 250, 1);
Setting h3_set = Setting(h3_set_txt, 0, &h3, 0, 250, 1);

const char h_menu_text_1[] PROGMEM = "<";
const char h_menu_text_2[] PROGMEM = "Heater 1";
const char h_menu_text_3[] PROGMEM = "Heater 2";
const char h_menu_text_4[] PROGMEM = "Heater 3";
const char * const h_menu_text[] PROGMEM= {h_menu_text_1, h_menu_text_2, h_menu_text_3, h_menu_text_4};
Menu * h_menu_items[] = {NULL, &h1_set, &h2_set, &h3_set};

int8_t h_selection = 0;
List h_menu = List(h_menu_text, h_menu_items, 4, &h_selection);

////////////////////////////////////////////////////////////////////

const char spool_ir_set_txt[] PROGMEM = "Spool I.R. (mm)";
const char spool_or_set_txt[] PROGMEM = "Spool ht (mm)";
const char spool_height_set_txt[] PROGMEM = "Spool I.R. (mm)";
Setting spool_ir_set = Setting(spool_ir_set_txt, 1, &spool_ir, 5, 500, 0.5);
Setting spool_or_set = Setting(spool_or_set_txt, 1, &spool_or, 10, 500, 0.5);
Setting spool_height_set = Setting(spool_height_set_txt, 1, &spool_height, 5, 500, 0.5);

const char spool_text_1[] PROGMEM = "<";
const char spool_text_2[] PROGMEM = "Inner Size";
const char spool_text_3[] PROGMEM = "Outer Size";
const char spool_text_4[] PROGMEM = "Height";
const char * const  spool_text[] PROGMEM = {spool_text_1, spool_text_2, spool_text_3, spool_text_4};
Menu * spool_items[] = {NULL, &spool_ir_set, &spool_or_set, &spool_height_set};

int8_t spool_selection = 0;
List spool_menu = List(spool_text, spool_items, 4, &spool_selection);

////////////////////////////////////////////////////////////////////

const char speed_set_txt[] PROGMEM = "Speed (mm/sec)";
Setting speed_set = Setting(speed_set_txt, 1, &speed, 5, 1000, 1);

const char settings_text_1[] PROGMEM = "<";
const char settings_text_2[] PROGMEM = "Thermal Zones";
const char settings_text_3[] PROGMEM = "Spool Size";
const char settings_text_4[] PROGMEM = "Extrude Speed";
const char * const  settings_text[] PROGMEM = {settings_text_1,settings_text_2,settings_text_3,settings_text_4};

Menu * settings_items[4] = {NULL, &h_menu, &spool_menu, &speed_set};

int8_t settings_selection = 0;
List settings_menu = List(settings_text, settings_items, 4, &settings_selection);

////////////////////////////////////////////////////////////////////
Action run_act = Action(&run, true);

const char main_menu_text_1[] PROGMEM = "Run/Stop";
const char main_menu_text_2[] PROGMEM = "Settings";
const char * const  main_menu_text[] PROGMEM = {main_menu_text_1,main_menu_text_2};
Menu * main_menu_items[] = {&run_act, &settings_menu};

int8_t main_menu_selection = 0;
List main_menu = List(main_menu_text, main_menu_items, 2, &main_menu_selection);
/*bool running = true;
bool params_changed = true;
float spool_id = 25;
float spool_od = 80;
float spool_height = 45;
float speed = 100;
float h1 = 30;
float h2 = 30;
float h3 = 30;
byte spooler_status = STATUS_UNKNOWN;
byte main_status = STATUS_UNKNOWN;*/
#define SCHEDULER_DEBUG
Scheduler scheduler;
char buffer[16];

void setup()
{
//#ifdef SCHEDULER_DEBUG
  Serial.begin(115200);
//#endif
  start_i2c();
  
  start_encoder();
  start_lcd();
  
  scheduler.add_task(handle_display,20000,5000);
  scheduler.add_task(handle_i2c,2000,500);
  
  scheduler.add_task(update_h1,20000,500);
  scheduler.add_task(update_h2,20000,500);
  scheduler.add_task(update_h3,20000,500);
  scheduler.add_task(update_speed,20000,500);
  
  scheduler.add_task(update_spool_ir,20000,500);
  scheduler.add_task(update_spool_or,20000,500);
  scheduler.add_task(update_spool_height,20000,500);
  scheduler.add_task(update_spool_speed,20000,500);
 
  scheduler.add_task(update_tz1,1000000,1000);
  scheduler.add_task(update_tz2,1000000,1000);
  scheduler.add_task(update_tz3,1000000,1000);
  scheduler.add_task(update_tz4,1000000,1000);
  scheduler.add_task(update_extrude_speed,10000,500);
  scheduler.add_task(update_main_status,10000,500);
  
  scheduler.add_task(update_spool_status,100000,5000);
  scheduler.add_task(update_v24,10000,5000);
}

void loop()
{
  uint8_t task = scheduler.round_robin();
#ifdef SCHEDULER_DEBUG
  scheduler.run_task(task,true);
#else
  scheduler.run_task(task,false);
#endif
}

void handle_display()
{
  main_menu.handle();
}

void update_h1()
{
  //static float last = 0;
  //if (h1 != last)
  //{
    send_float(h1, 0x30, 0x12);
  //  last = h1;
  //}
}

void update_h2()
{
  //static float last = 0;
  //if (h2 != last)
  //{
    send_float(h2, 0x31, 0x12);
  //  last = h2;
  //}
}

void update_h3()
{
  //static float last = 0;
  //if (h3 != last)
  //{
    send_float(h3, 0x32, 0x12);
  //  last = h3;
  //}
}

void update_spool_ir()
{
  //static float last = 0;
  //if (spool_ir != last)
  //{
    send_float(spool_ir, 0x41, 0x11);
  //  last = spool_ir;
  //}
}

void update_spool_or()
{
  //static float last = 0;
  //if (spool_or != last)
  //{
    send_float(spool_or, 0x42, 0x11);
  //  last = spool_or;
  //}
}

void update_spool_height()
{
  //static float last = 0;
  //if (spool_height != last)
  //{
    send_float(spool_height, 0x43, 0x11);
  //  last = spool_height;
  //}
}

void update_spool_speed()
{
  //static float last = 0;
  //if (extrude_speed != last)
  //{
    send_float(extrude_speed, 0x40, 0x11);
 //   last = extrude_speed;
  //}
}

void update_speed()
{
  //static float last = 0;
  //if (speed != last)
  //{
    send_float(speed, 0x40, 0x12);
  //  last = speed;
  //} 
}

//void get_float(byte request, byte address, float * value);
void update_tz1()
{
  get_float(0x20, 0x12, &tz1);
}

void update_tz2()
{
  get_float(0x21, 0x12, &tz2);
}

void update_tz3()
{
  get_float(0x22, 0x12, &tz3);
}

void update_tz4()
{
  get_float(0x23, 0x12, &tz4);
}

void update_extrude_speed()
{
  get_float(0x43, 0x12, &extrude_speed);
}

void update_v24()
{
  get_float(0x10, 0x11, & v24);
  Serial.println(v24);
}

void update_spool_status()
{
  get_byte(0x00, 0x11, & spool_status);
}

void update_main_status()
{
  get_byte(0x00, 0x12, & main_status);
}

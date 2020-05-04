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
float tz1 = 35;
float tz2 = 35;
float tz3 = 35;
float spool_ir = 25;
float spool_or = 80;
float spool_height = 40;
float speed = 100;

////////////////////////////////////////////////////////////////////
Setting h1_set = Setting("Heater 1 (C)", 14, 0, &h1, 0, 250, 1);
Setting h2_set = Setting("Heater 2 (C)", 14, 0, &h2, 0, 250, 1);
Setting h3_set = Setting("Heater 3 (C)", 14, 0, &h3, 0, 250, 1);

String h_menu_text[4] = {"<", "Heater 1","Heater 2","Heater 3"};
Menu * h_menu_items[4] = {NULL, &h1_set, &h2_set, &h3_set};

int8_t h_selection = 0;
List h_menu = List(h_menu_text, h_menu_items, 4, &h_selection);
////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////
Setting spool_ir_set = Setting("Spool I.R. (mm)", 15, 1, &spool_ir, 5, 500, 0.5);
Setting spool_or_set = Setting("Spool O.R. (mm)", 15, 1, &spool_or, 10, 500, 0.5);
Setting spool_height_set = Setting("Spool ht (mm)", 13, 1, &spool_height, 5, 500, 0.5);

String spool_text[4] = {"<", "Inner Size","Outer Size","Height"};
Menu * spool_items[4] = {NULL, &spool_ir_set, &spool_or_set, &spool_height_set};

int8_t spool_selection = 0;
List spool_menu = List(spool_text, spool_items, 4, &spool_selection);
////////////////////////////////////////////////////////////////////

Setting speed_set = Setting("Speed (mm/sec)", 14, 1, &speed, 5, 1000, 1);


String settings_text[4] = {"<", "Thermal Zones","Spool Size","Extrude Speed"};
Menu * settings_items[4] = {NULL, &h_menu, &spool_menu, &speed_set};

int8_t settings_selection = 0;
List settings_menu = List(settings_text, settings_items, 4, &settings_selection);


String main_menu_text[1] = {"Settings"};
Menu * main_menu_items[1] = {&settings_menu};

int8_t main_menu_selection = 0;
List main_menu = List(main_menu_text, main_menu_items, 1, &main_menu_selection);
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
void setup()
{
#ifdef SCHEDULER_DEBUG
  Serial.begin(115200);
#endif

  start_encoder();
  start_lcd();
  start_i2c();
  
  scheduler.add_task(handle_display,20000,5000);
  scheduler.add_task(handle_i2c,1000,500);
}
void loop()
{
  uint8_t task = scheduler.shortest_response_time();
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
/*
volatile bool loading = false;
volatile bool render_now = true;
void setup() 
{ 
 
 
 lcd.createChar(BACKSLASH,BACKSLASH_BYTES);
 lcd.createChar(HOURGLASS_FULL,HOURGLASS_FULL_BYTES);
 lcd.createChar(HOURGLASS_MID,HOURGLASS_MID_BYTES);
 lcd.createChar(HOURGLASS_EMPTY,HOURGLASS_EMPTY_BYTES);
 
 lcd.setCursor(0, 0); //jump to second colum, first row
 lcd.print("INTERFACE BOARD"); //print welcome
 lcd.setCursor(0, 1); //jump to second colum, first row
 lcd.print("INITIALIZING..."); //print welcome
 
 lcd.setCursor(0, 1);
 lcd.print("PIN INIT...    ");
 pinMode(ENC_A, INPUT);
 pinMode(ENC_B, INPUT);
 pinMode(ENC_SW, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(ENC_A),isrEncoder,CHANGE);
 attachInterrupt(digitalPinToInterrupt(ENC_SW),isrButton,FALLING);
 
 lcd.setCursor(0, 1);
 lcd.print("I2C CLAIM...    ");
 Wire.begin(); //join i2c bus as master
}
//º
void loop() 
{
  render();
}

void render()
{
  static uint8_t loading_loop_step = 0;
  static long last_time = millis();

  if ((millis()-last_time > 250) && (loading==true))
  {
    render_now = true;
    last_time = millis();
  }

  if(render_now)
  {
    noInterrupts();
    lcd.setCursor(15, 1);
    if (loading)
    {
      lcd.write(byte(HOURGLASS_FULL+min(2,loading_loop_step)));
      loading_loop_step++;
      if (loading_loop_step==5)
      loading_loop_step = 0;
    }
    else
      lcd.print(" ");
    interrupts();
    render_now = false;
  }
  
}

*/

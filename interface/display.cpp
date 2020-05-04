#include "display.hpp"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

extern long enc_delta;
extern bool button_pressed;

char line_buffer[16];

void start_lcd()
{
  pinMode(LCD_RS,OUTPUT);
  pinMode(LCD_EN,OUTPUT);
  pinMode(LCD_DB4,OUTPUT);
  pinMode(LCD_DB5,OUTPUT);
  pinMode(LCD_DB6,OUTPUT);
  pinMode(LCD_DB7,OUTPUT);
  lcd.begin(16,2);
}

Setting::Setting(const char s_caption[], uint8_t s_decimals, float * s_target_val, float s_min_val, float s_max_val, float s_delta_val)
{
   caption = s_caption;
   target_val = s_target_val;
   new_val = *target_val;
   min_val = s_min_val;
   max_val = s_max_val;
   delta_val = s_delta_val;
   decimals = s_decimals;
}

bool Setting::handle()
{
  if(button_pressed)
  {
    *target_val = new_val;
    button_pressed = false;
    return true;
  }
  if((first_time) || (enc_delta))
  {
    if (abs(enc_delta) < 10)
      new_val = min(max_val,max(min_val,new_val+delta_val*((float)enc_delta)));
    enc_delta = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(read_progmem_string(caption));
    
    lcd.setCursor(0,1);
    lcd.print(*target_val,decimals);
    lcd.print(" ");
    lcd.print(new_val,decimals);
    
    first_time = false;
  }
  return false;
}


List::List(const char * const * const s_entries, Menu * s_targets[],  int8_t s_num_entries, int8_t *s_selected)
{
  selected = s_selected;
  selection = *selected;
  num_entries = min(16,s_num_entries);
  entries = s_entries;
  for (int i = 0; i < num_entries; i++)
  {
    targets[i] = s_targets[i];
  }
}
bool List::handle()
{
  if (!in_submenu)
  {
    if((first_time) || (enc_delta))
    {
      if (abs(enc_delta) < 2)
      {
        last_selection = selection;
  
        selection -= enc_delta;
        enc_delta = 0;
        
        if (selection >= num_entries)
          selection = 0;
        if (selection < 0)
          selection = num_entries - 1;
      }
        
      lcd.clear();
      lcd.setCursor(0,0);
      if ((selection < last_selection)|| (selection == 0))
      {
        lcd.print(">");
        strcpy_P(line_buffer, (char *) pgm_read_word(&(entries[selection])));
        lcd.print(line_buffer);
        if (num_entries >1)
        {
          lcd.setCursor(0,1);
          lcd.print(" ");
          strcpy_P(line_buffer, (char *) pgm_read_word(&(entries[selection+1])));
          lcd.print(line_buffer);
        }
      }
      else
      {
        lcd.print(" ");
        strcpy_P(line_buffer, (char *) pgm_read_word(&(entries[selection-1])));
        lcd.print(line_buffer);
        lcd.setCursor(0,1);
        lcd.print(">");
        strcpy_P(line_buffer, (char *) pgm_read_word(&(entries[selection])));
        lcd.print(line_buffer);
      }
      first_time = false;
    }
    if(button_pressed)
    {
      button_pressed = false;
      *selected = selection;
      if (targets[selection] == NULL)
      {
        return true;
      }
      targets[selection]->make_first_time();
      
      in_submenu = true;
    }
  }
  else
  {
    first_time = true;
    if(targets[selection]->handle())
    {
        in_submenu = false;
    }
  }
  return false;
}

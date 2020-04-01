#include <LiquidCrystal.h>
#include "../common/i2c.h"
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

void setup() 
{
   lcd.begin(16, 2); //initialize the LCD as a 16 row by 2 column display
   lcd.print("INTERFACE BOARD\nINITIALIZING..."); //print welcome
   lcd.setCursor(0, 1); //jump to second colum, first row
   lcd.print("I2C CLAIM...");
   Wire.begin(); //join i2c bus as master
}

void loop() 
{
  
}

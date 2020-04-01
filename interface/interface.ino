#include <LiquidCrystal.h>
#include "../common/i2c.h"
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() 
{
   lcd.begin(16, 2); //initialize the LCD 
   lcd.print("INTERFACE BOARD\nINITIALIZING...");
   lcd.setCursor(0, 1);
   lcd.print("I2C CLAIM...");
}

void loop() 
{
  
}

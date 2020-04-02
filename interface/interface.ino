#include <LiquidCrystal.h>
#include <Wire.h>
#include "i2c.h"
#include "pins.h"
#include "lcd_chars.h"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_DB4, LCD_DB5, LCD_DB6, LCD_DB7);

volatile int32_t encoder_delta = 0;
volatile bool sw_pushed = false;
void setup() 
{ 
 pinMode(LCD_RS,OUTPUT);
 pinMode(LCD_EN,OUTPUT);
 pinMode(LCD_DB4,OUTPUT);
 pinMode(LCD_DB5,OUTPUT);
 pinMode(LCD_DB6,OUTPUT);
 pinMode(LCD_DB7,OUTPUT);
 lcd.begin(16, 2); //initialize the LCD as a 16 row by 2 column display
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
  noInterrupts();
  static uint8_t loading_loop_step = 0;
  lcd.setCursor(15, 1);
  lcd.write(byte(HOURGLASS_FULL+min(2,loading_loop_step)));
  loading_loop_step++;
  if (loading_loop_step==5)
    loading_loop_step = 0;
  /*static int32_t encoder_delta_last = 0;
  while(encoder_delta_last == encoder_delta)
  {}*/
  /*
  sw_pushed = false;
  //encoder_delta_last = encoder_delta;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENCODER DELTA:");
  lcd.setCursor(0, 1);
  
  
  lcd.print(encoder_delta);
  lcd.print(" ");
  /*for(int i = 0; i < 8; i++)
  {
    lcd.print((PIND & 1 << i)>>i);
  }*/
  //lcd.print(" ");
  
  interrupts();
  delay(250);
}

void isrEncoder()
{
  if (((ENC_PULSE_PORT & ENC_A_MASK) == 0) == ((ENC_PULSE_PORT & ENC_B_MASK) == 0))
    encoder_delta++;
  else
    encoder_delta--;
}

void isrButton()
{
  sw_pushed=true;
}

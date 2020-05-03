#ifndef PINS_H
#define PINS_H

//LCD pins
#define LCD_DB4           A0
#define LCD_DB5           A1
#define LCD_DB6           A2
#define LCD_DB7           A3
#define LCD_EN            11
#define LCD_RS            12

//rotary encoder pins
#define ENC_PULSE_PORT    PIND
#define ENC_A             2
#define ENC_A_MASK        0b00000100
#define ENC_B             4
#define ENC_B_MASK        0b00010000
#define ENC_SW            3

//spare test points
#define TP2       9
#define TP3       10

#endif

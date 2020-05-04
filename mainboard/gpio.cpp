#include "pins.h"
#include "gpio.hpp"
// The thermal probes are a resistance of 100kohm at 25 degrees C, with a B value of 3950.

float grind_speed = 0;
float extrude_speed = 0;
float target_h1 = 0;
float target_h2 = 0;
float target_h3 = 0;

extern bool running;

void handle_h1()
{
  static int8_t p = 0;
  float temp = get_tz(PIN_TZ1);
  p = min(100,max(-100,p+((temp < target_h1*0.95)-((temp > target_h1*1.05)))));
  digitalWrite(PIN_H1,(p > 0)&& running);
}
void handle_h2()
{
  static int8_t p = 0;
  float temp = get_tz(PIN_TZ2);
  p = min(100,max(-100,p+((temp < target_h2*0.95)-((temp > target_h2*1.05)))));
  digitalWrite(PIN_H2,(p > 0)&& running);
}
void handle_h3()
{
  static int8_t p = 0;
  float temp = get_tz(PIN_TZ3);
  p = min(100,max(-100,p+((temp < target_h3*0.95)-((temp > target_h3*1.05)))));
  digitalWrite(PIN_H3,(p > 0)&& running);
}

void handle_extruder()
{
  static int8_t p = 0;
  p = min(100,max(-100,p
                       +(get_tz(PIN_TZ1) > target_h1*0.9)
                       -(get_tz(PIN_TZ1) < target_h1*0.9)
                       +(get_tz(PIN_TZ2) > target_h2*0.9)
                       -(get_tz(PIN_TZ2) < target_h2*0.9)
                       +(get_tz(PIN_TZ3) > target_h3*0.9)
                       -(get_tz(PIN_TZ3) < target_h3*0.9)));
  extrude_speed = ((p > 0) && running)*speed;
  digitalWrite(PIN_EXTRUDE,((p > 0) && running));
}

#define GRIND_SPEED 128
void handle_grinder()
{
  analogWrite(PIN_GRIND,(running)*GRIND_SPEED);
  grind_speed = (running)*GRIND_SPEED;
}

float get_tz(uint8_t pin, int offset = 5)
{
  return ((293.15*3950)/(293.15*log((1024.0/(analogRead(pin)+offset)-1)/100)+3950))-273.15;
}

uint32_t get_ac_pl()
{
  static uint32_t last_zc_micros = micros();
  static bool last_state = 0;
  if (last_state ^ ((PINB & 0b00010000)>>4))
  {
    last_state = !last_state;
    last_zc_micros = micros();
  }
  return last_zc_micros;
}
#define MICROS_60HZ 16667

/*class Triac
{
  private:
    float trigger = MICROS_60HZ;
    uint8_t pin = 0;
  public: 
    Heater (uint8_t pin_val)
    {
      pin = pin_val;
      pinMode(pin, OUTPUT);
      digitalWrite(pin,LOW);
    }
    void set (uint8_t percent) { trigger_phase = asin(percent); }
    void handle (float last_trigger)
    {
      
    }
    
};*/

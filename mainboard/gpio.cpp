#include "pins.h"
// The thermal probes are a resistance of 100kohm at 25 degrees C, with a B value of 3950.


float get_tz(uint8_t pin, int offset = 5)
{
  return ((293.15*3950)/(293.15*log((1024.0/(analogRead(pin)+offset)-1)/100)+3950))-273.15;
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

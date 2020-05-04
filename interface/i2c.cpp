#include "i2c.hpp"


void start_i2c()
{
  Wire.begin();
}

void handle_i2c()
{
}


Param * params;
uint8_t num_params = 0;



uint8_t add_param(float value, uint8_t target)
{
  if (num_params < MAX_PARAMS)
  {
    params[num_params] = * new Param(value, target);
    num_params++;
    return num_params-1;
  }
  return 0xFF;
}

void set_param(uint8_t param, float value)
{
  params[param].set(value);
}

void tx_params()
{
  for(int i = 0; i < num_params; i++)
  {
    params[i].tx();
  }
}

Param::Param(float s_value, uint8_t s_target)
{
  value = s_value;
  target = s_target;
}
void Param::set(float s_value)
{
  value = s_value;
  updated = true;
}

void Param::tx()
{
  if (updated)
  {
    byte* data = (byte *) &value;
    Wire.beginTransmission(target);
    Wire.write(data[0]);
    Wire.write(data[1]);
    Wire.write(data[2]);
    Wire.write(data[3]);
    Wire.endTransmission();
    delayMicroseconds(PARAM_WRITE_DELAY);
    updated = true;
  }
}

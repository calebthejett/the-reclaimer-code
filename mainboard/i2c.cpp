#include "i2c.hpp"
#include "gpio.hpp"
#include "pins.h"
#include <Arduino.h>
#include "gpio.hpp"


extern float target_h1;
extern float target_h2;
extern float target_h3;
extern float speed;
extern float grind_speed;
extern float extrude_speed;

extern uint8_t status;
extern bool running;

volatile char i2c_buffer[I2C_BUFFER_LEN];
uint8_t i2c_length;

volatile char resp_buffer[I2C_BUFFER_LEN];
uint8_t resp_length;



void init_i2c()
{
  Wire.begin(I2C_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}




void receiveEvent(int howMany)
{
  while (Wire.available())
  {
    if (i2c_length < I2C_BUFFER_LEN)
    {
      i2c_buffer[i2c_length] = Wire.read();
      i2c_length++;
    }
    else
    {
      status = STAT_I2C_ERR;
    }
  }
}

void requestEvent()
{
  Wire.write(resp_length);
  for (int i = 0; i < resp_length; i++)
  {
    Wire.write(resp_buffer[i]);
  }
}


void proc_i2c()
{
  #ifdef DEBUG
  if(Serial.available())
  {
    delay(50);
    while(Serial.available())
    {
      if (i2c_length < I2C_BUFFER_LEN)
      {
        i2c_buffer[i2c_length] = Serial.read();
        i2c_length++;
      }
      else
      {
        status = STAT_I2C_ERR;
      }
    }
  }
  if(resp_length)
  {
    Serial.write((char*)resp_buffer, I2C_BUFFER_LEN);
    resp_length = 0;
  }
  #endif
  while(i2c_length)
  {
    switch(i2c_buffer[0])
    {
      case MSG_GET_STATUS:
      {
        i2c_length -= 1;
        resp_buffer[0] = MSG_GET_STATUS;
        resp_buffer[1] = status;
        resp_length = 2;
        break;
      }
      case MSG_GET_TZ1:
      {
        i2c_length -= 1;
        float temp = get_tz(PIN_TZ1);
        byte* data = (byte *) &temp;
        resp_buffer[0] = MSG_GET_TZ1;
        resp_buffer[1] = data[0];
        resp_buffer[2] = data[1];
        resp_buffer[3] = data[2];
        resp_buffer[4] = data[3];
        resp_length = 5;
        break;
      }
      case MSG_GET_TZ2:
      {
        i2c_length -= 1;
        float temp = get_tz(PIN_TZ2);
        byte* data = (byte *) &temp;
        resp_buffer[0] = MSG_GET_TZ2;
        resp_buffer[1] = data[0];
        resp_buffer[2] = data[1];
        resp_buffer[3] = data[2];
        resp_buffer[4] = data[3];
        resp_length = 5;
        break;
      }
      case MSG_GET_TZ3:
      {
        i2c_length -= 1;
        float temp = get_tz(PIN_TZ3);
        byte* data = (byte *) &temp;
        resp_buffer[0] = MSG_GET_TZ3;
        resp_buffer[1] = data[0];
        resp_buffer[2] = data[1];
        resp_buffer[3] = data[2];
        resp_buffer[4] = data[3];
        resp_length = 5;
        break;
      }
      case MSG_GET_TZ4:
      {
        i2c_length -= 1;
        float temp = get_tz(PIN_TZ4);
        byte* data = (byte *) &temp;
        resp_buffer[0] = MSG_GET_TZ4;
        resp_buffer[1] = data[0];
        resp_buffer[2] = data[1];
        resp_buffer[3] = data[2];
        resp_buffer[4] = data[3];
        resp_length = 5;
        break;
      }
      case MSG_SET_H1:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        target_h1 = bytes_to_float(data);
        break;
      }
      case MSG_SET_H2:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        target_h2 = bytes_to_float(data);
        break;
      }
      case MSG_SET_H3:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        target_h3 = bytes_to_float(data);
        break;
      }
      case MSG_SET_SPEED:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        speed = bytes_to_float(data);
        break;
      }
      case MSG_SET_GRIND_SPEED:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        grind_speed = bytes_to_float(data);
        break;
      }
      case MSG_SET_EXTRUDE_SPEED:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        extrude_speed = bytes_to_float(data);
        break;
      }
      case MSG_RUN:
      {
        i2c_length -= 1;
        running = true;
        break;
      }
      case MSG_STOP:
      {
        i2c_length -= 1;
        running = false;
        speed = 0;
        grind_speed = 0;
        extrude_speed = 0;
        target_h1 = 0;
        target_h2 = 0;
        target_h3 = 0;
        status = STAT_READY;
        
        break;
      }
    }
  }
}

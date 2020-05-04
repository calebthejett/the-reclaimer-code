#include "i2c.hpp"
#include "gpio.hpp"
#include <Arduino.h>
#include "common.hpp"
#include "gpio.hpp"

volatile char i2c_buffer[I2C_BUFFER_LEN];
int i2c_length;

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
      case MSG_GET_24V:
      {
        i2c_length -= 1;
        float f_voltage = get_24vfb();
        byte* data = (byte *) &f_voltage;
        resp_buffer[0] = MSG_GET_24V;
        resp_buffer[1] = data[0];
        resp_buffer[2] = data[1];
        resp_buffer[3] = data[2];
        resp_buffer[4] = data[3];
        resp_length = 5;
        break;
      }
      case MSG_SET_MOTOR_SPEED:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        motor_speed = bytes_to_float(data);
        break;
      }
      case MSG_GET_MOTOR_SPEED:
      {
        i2c_length -= 1;
        byte* data = (byte *) &motor_speed;
        resp_buffer[0] = MSG_GET_MOTOR_SPEED;
        resp_buffer[1] = data[0];
        resp_buffer[2] = data[1];
        resp_buffer[3] = data[2];
        resp_buffer[4] = data[3];
        resp_length = 5;
        break;
      }
      case MSG_SET_SERVO_ANGLE:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        servo_angle = bytes_to_float(data);
        break;
      }
      case MSG_GET_SERVO_ANGLE:
      {
        i2c_length -= 1;
        byte* data = (byte *) &servo_angle;
        resp_buffer[0] = MSG_GET_SERVO_ANGLE;
        resp_buffer[1] = data[0];
        resp_buffer[2] = data[1];
        resp_buffer[3] = data[2];
        resp_buffer[4] = data[3];
        resp_length = 5;
        break;
      }
      case MSG_SET_SPOOL_SPEED:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        spool_speed = bytes_to_float(data);
        break;
      }
      case MSG_SET_SPOOL_ID:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        spool_id = bytes_to_float(data);
        break;
      }
      case MSG_SET_SPOOL_OD:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        spool_od = bytes_to_float(data);
        break;
      }
      case MSG_SET_SPOOL_HEIGHT:
      {
        i2c_length -= 5;
        byte data[4] = {i2c_buffer[1], i2c_buffer[2], i2c_buffer[3], i2c_buffer[4]};
        spool_height = bytes_to_float(data);
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
        motor_speed = 0;
        servo_angle = 90;
        break;
      }
      case MSG_RESET:
      {
        i2c_length -=1;
        reset();
        break;
      }
      default:
      {
        i2c_length -=1;
      }
    }
  }
}

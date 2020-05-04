#include "i2c.hpp"


void start_i2c()
{
  Wire.begin();
}

void handle_i2c()
{
}

void tx_float(float value, byte address)
{
  byte* data = (byte *) &value;
  Wire.beginTransmission(address);
  Wire.write(data[0]);
  Wire.write(data[1]);
  Wire.write(data[2]);
  Wire.write(data[3]);
  Wire.endTransmission();
  delayMicroseconds(WRITE_DELAY);
}

void tx_byte(byte value, byte address)
{
  Wire.beginTransmission(address);
  Wire.write(value);
  Wire.endTransmission();
  delayMicroseconds(WRITE_DELAY);
}

byte recv_float(byte address, float * value)
{
  byte val; // the code that the slave is responding to
  byte recv[4];
  Wire.requestFrom(address,5);
  val = Wire.read();
  for(int i = 0; i < 4; i++)
  {
    recv[i] = Wire.read();
  }
  *value = bytes_to_float(recv);
  return val;
}

byte recv_byte(byte address, byte * value)
{
  byte val; // the code that the slave is responding to
  Wire.requestFrom(address,2);
  delayMicroseconds(READ_DELAY);
  val = Wire.read();
  *value = Wire.read();
  return val;
}

void get_float(byte request, byte address, float * value)
{
  tx_byte(request,address);
  recv_float(address,value);
}

void get_byte(byte request, byte address, byte * value)
{
  tx_byte(request,address);
  delayMicroseconds(READ_DELAY);
  recv_byte(address,value);
}


void send_float(float value, byte code, byte address)
{
  byte* data = (byte *) &value;
  Wire.beginTransmission(address);
  Wire.write(code);
  Wire.write(data[0]);
  Wire.write(data[1]);
  Wire.write(data[2]);
  Wire.write(data[3]);
  Wire.endTransmission();
  delayMicroseconds(WRITE_DELAY);
  
}
void send_byte(byte value, byte code, byte address)
{
  Wire.beginTransmission(address);
  Wire.write(code);
  Wire.write(value);
  Wire.endTransmission();
  delayMicroseconds(WRITE_DELAY);
}

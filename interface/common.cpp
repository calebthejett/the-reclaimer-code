#include "common.hpp"

bool running = false;
bool run()
{
  running = !running;
  if (running)
  {
    tx_byte(0x01,0x10);
    delay(100);
    tx_byte(0x02,0x10);
    delay(100);
    tx_byte(0x03,0x10);
    delay(100);
    tx_byte(0x04,0x10);
    delay(100);
    tx_byte(0x06,0x10);
    delay(100);
    tx_byte(0x50,0x11);
    tx_byte(0x50,0x12);
  }
  else
  {
    tx_byte(0x05,0x10);
    delay(100);
    tx_byte(0x07,0x10);
    delay(100);
    tx_byte(0x51,0x11);
    tx_byte(0x51,0x12);
    tx_byte(0x60,0x11);
  }
  return true;
}

float bytes_to_float(byte * fourbytes)
{
  union u_tag {
    byte b[4];
    float fval;
  } u;
  u.b[0] = fourbytes[0];
  u.b[1] = fourbytes[1];
  u.b[2] = fourbytes[2];
  u.b[3] = fourbytes[3];
  return u.fval;
}

String read_progmem_string(const char source[])
{
  String val = "";
  for(int i = source; i < source+strlen_P(source); i++)
  {
    val += (char)pgm_read_byte_near(i);
  }
  return val;
}
/*void run()
{
  if (running)
  {
    
  }
}*/

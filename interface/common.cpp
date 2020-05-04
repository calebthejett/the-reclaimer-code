#include "common.hpp"

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

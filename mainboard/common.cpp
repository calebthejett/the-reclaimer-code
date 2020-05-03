#include "common.hpp"
#include <Arduino.h>

bool running = false;

uint8_t status = STAT_READY;

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

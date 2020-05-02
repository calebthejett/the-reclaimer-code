#ifndef COMMON_HPP
#define COMMON_HPP

#include <Arduino.h>

#define STAT_OK 0xFF
#define STAT_I2C_ERR 0x10
#define STAT_FULL 0x20

float bytes_to_float(byte * fourbytes);



#endif

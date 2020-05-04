#ifndef COMMON_HPP
#define COMMON_HPP

#include <Arduino.h>

#define STAT_ESTOP 0x00

#define STAT_I2C_ERR 0x10

#define STAT_NOFEED 0x20
#define STAT_HEATING 0x21
#define STAT_RUNNING 0x22

#define STAT_READY 0xFF

typedef void (*fp) (void);

float bytes_to_float(byte * fourbytes);


#endif

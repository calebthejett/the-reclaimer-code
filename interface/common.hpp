#ifndef COMMON_HPP
#define COMMON_HPP
#include <Arduino.h>
#include "i2c.hpp"

#define STATUS_UNKNOWN 0xFE

typedef void (*fp) (void);
typedef bool (*fp_bool) (void);

bool run();

float bytes_to_float(byte * fourbytes);
String read_progmem_string(const char source[]);

#endif

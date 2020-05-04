#ifndef COMMON_HPP
#define COMMON_HPP
#include <Arduino.h>

#define STATUS_UNKNOWN 0xFE
void run();

float bytes_to_float(byte * fourbytes);
String read_progmem_string(const char source[]);

#endif

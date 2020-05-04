#ifndef I2C_HPP
#define I2C_HPP

#include <Wire.h>
#include <Arduino.h>
#include "common.hpp"

#define MAX_PARAMS 16
#define WRITE_DELAY 10000
#define READ_DELAY 10000


void start_i2c();
void handle_i2c();

void tx_float(float value, byte address);
void tx_byte(byte value, byte address);

byte recv_float(byte address, float * value);
byte recv_byte(byte address, byte * value);

void get_float(byte request, byte address, float * value);
void get_byte(byte request, byte address, byte * value);

void send_float(float value, byte code, byte address);
void send_byte(byte value, byte code, byte address);
#endif

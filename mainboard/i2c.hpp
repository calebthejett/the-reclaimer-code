#ifndef I2C_HPP
#define I2C_HPP

#include <Wire.h>
#include "gpio.hpp"
#include "common.hpp"

#define I2C_ADDR 0x12
#define I2C_BUFFER_LEN 16

#define MSG_GET_STATUS 0x10

#define MSG_GET_TZ1 0x20
#define MSG_GET_TZ2 0x21
#define MSG_GET_TZ3 0x22
#define MSG_GET_TZ4 0x23

#define MSG_SET_H1 0x30
#define MSG_SET_H2 0x31
#define MSG_SET_H3 0x32

#define MSG_SET_SPEED 0x40
#define MSG_SET_GRIND_SPEED 0x41
#define MSG_SET_EXTRUDE_SPEED 0x42

#define MSG_RUN 0x50
#define MSG_STOP 0x51


void proc_i2c();
void requestEvent();
void receiveEvent(int howMany);
void init_i2c();

#endif

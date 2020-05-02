#ifndef I2C_HPP
#define I2C_HPP

#include <Wire.h>

#define I2C_ADDR 0x11
#define I2C_BUFFER_LEN 16

#define MSG_GET_STATUS 0x00

#define MSG_GET_24V 0x10          //float32, volts

#define MSG_SET_MOTOR_SPEED 0x20  //float32, rpm
#define MSG_GET_MOTOR_SPEED 0x21  //float32, rpm

#define MSG_SET_SERVO_ANGLE 0x30  //float32, degrees
#define MSG_GET_SERVO_ANGLE 0x31  //float32, degrees

#define MSG_SET_SPOOL_SPEED 0x40  //float32, mm/s
#define MSG_SET_SPOOL_ID 0x41     //float32, mm
#define MSG_SET_SPOOL_OD 0x42     //float32, mm
#define MSG_SET_SPOOL_HEIGHT 0x43 //float32, mm

#define MSG_RUN 0x50
#define MSG_STOP 0x51

extern uint8_t status;
extern float motor_speed;
extern float servo_angle;
extern float spool_speed;
extern float spool_id;
extern float spool_od;
extern float spool_height;
extern bool running;




void proc_i2c();
void requestEvent();
void receiveEvent(int howMany);
void init_i2c();

#endif

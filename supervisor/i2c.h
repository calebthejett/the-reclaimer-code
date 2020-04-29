#ifndef I2C_H
#define I2C_H

#define I2C_SLAVE_ADDRESS 0x10

#define MSG_ESTOP 0x00

#define MSG_MAINBOARD_OK  0x01
#define MSG_IFBOARD_OK  0x02
#define MSG_SPOOLBOARD_OK 0x03

#define MSG_120V_ON 0x04
#define MSG_120V_OFF 0x05
#define MSG_24V_ON 0x06
#define MSG_24V_OFF 0x07

#define MSG_BEEP_OFFSET 0x10

#endif

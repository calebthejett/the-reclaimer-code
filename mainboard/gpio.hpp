#ifndef GPIO_HPP
#define GPIO_HPP

extern float speed;

float get_tz(uint8_t pin, int offset = 5);
uint32_t get_ac_pl();
void handle_h1();
void handle_h2();
void handle_h3();
void handle_grinder();
void handle_extruder();

#endif

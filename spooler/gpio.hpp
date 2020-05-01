#ifndef GPIO_HPP
#define GPIO_HPP

#define MAX_24VFB 26.27


void gpio_init();

float get_24vfb();

void write_motor(float pct);

#endif

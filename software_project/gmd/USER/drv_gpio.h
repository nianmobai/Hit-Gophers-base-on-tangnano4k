#include "gw1ns4c.h"

int gpio_init(void);
int gpio_write(uint16_t data);
int gpio_read(uint16_t *data);
int gpio_setOut(uint16_t mask);
int gpio_setIn(uint16_t mask);

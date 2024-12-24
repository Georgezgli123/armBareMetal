#pragma once

#include "peripherals/gpio.h"
#include "utils.h"

typedef enum _gpio_func {
    GFInput = 0,
    GFOutput = 1,
    GFAlt0 = 4,
    GFAlt1 = 5,
    GFAlt2 = 6,
    GFAlt3 = 7,
    GFAlt4 = 3,
    GFAlt5 = 2 
} gpio_func;

void gpio_pin_set_func(u8 pin_number, gpio_func func);
void gpio_pin_enable(u8 pin_number);
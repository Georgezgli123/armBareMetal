#include "gpio.h"
#include "utils.h"
#include "peripherals/aux.h"
#include "mini_uart.h"

#define TXD 14
#define RXD 15

void uart_init() {
    gpio_pin_set_func(TXD, GFAlt5);
    gpio_pin_set_func(RXD, GFAlt5);
    
    gpio_pin_enable(TXD);
    gpio_pin_enable(RXD);

    REG_AUX->enables = 1;
    REG_AUX->mu_control = 0;
    REG_AUX->mu_ier = 0xD;
    REG_AUX->mu_lcr = 3;
    REG_AUX->mu_mcr = 0;

#if RPI_VERSION == 3
    REG_AUX->mu_baud_rate = 270; // 115200 @ 250 Mhz
#endif
#if RPI_VERSION == 4
    REG_AUX->mu_baud_rate = 541; // 115200 @ 500 Mhz
#endif
    REG_AUX->mu_control = 3;

    uart_send('\r');
    uart_send('\n');
    uart_send('\n');
}

void uart_send(char c) {
    while(!(REG_AUX->mu_lsr & 0x20));
    REG_AUX->mu_io = c;
}

char uart_recv() {
    while(!(REG_AUX->mu_lsr & 1));
    return REG_AUX->mu_io & 0xFF;
}

void uart_send_string(char *str) {
    while(*str) {
        if(*str == '\n') {
            uart_send('\r');
        }
        uart_send(*str);
        str++;
    }
}

#include "common.h"
#include "mini_uart.h"
#include "printf.h"
#include "irq.h"
#include "utils.h"
#include "timer.h"
#include "i2c.h"

void putc(void *p, char c) {
    if(c == '\n') {
        uart_send('\r');
    }
    uart_send(c);
}

void kernel_main() {
    uart_init();
    init_printf(0, putc);
    printf("Rasperry PI Bare Metal OS init\n");

    irq_init_vectors();
    enable_interrupt_controller();
    irq_enable();
    timer_init();
#if RPI_VERSION == 3
    printf("\tBoard: RPI 3\n");
#elif RPI_VERSION == 4
    printf("\tBoard: RPI 4");
#endif
    printf("\n\nDone, ported printf is using!\n");
    printf("\nException Level: %d\n", get_el());

    printf("Sleep 200ms ...\n");
    timer_sleep(200);
    printf("initializing i2c ...\n");
    i2c_init();
    u8 write_buf[1] = {0x00}; //write 0x00 id register
    u8 read_buf[1] = {0x00}; // read back the id (read only)
    u8 res;
    res = i2c_send(0x2a, write_buf, 1);
    if(res != 0) printf("write error: res = %d\n", res);
    res = i2c_recv(0x2a, read_buf, 1);
    if(res != 0) printf("read error: res = %d\n", res);
    printf("get buffer [0] = 0x%x\n", read_buf[0]);

    //enable leds
    u8 bl_en[2] = {0x01, 0x21};
    res = i2c_send(0x2a, bl_en, 2);
    if(res != 0) printf("write error: res = %d\n", res);
    //configure mode
    u8 cfg_en[2] = {0x04, 0x00};
    res = i2c_send(0x2a, cfg_en, 2);
    if(res != 0) printf("write error: res = %d\n", res);
    //set current
    u8 cur_bl[2] = {0x09, 0x2d};
    res = i2c_send(0x2a, cur_bl, 2);
    if(res != 0) printf("write error: res = %d\n", res);
    // enable leds
    u8 d_en[2] = {0x05, 0x00};
    res = i2c_send(0x2a, d_en, 2);
    if(res != 0) printf("write error: res = %d\n", res);

    printf("keep on 2 seconds, and turn off the leds\n");
    timer_sleep(2000);
    //turn off leds
    u8 d_dis[2] = {0x05, 0x7F};
    res = i2c_send(0x2a, d_dis, 2);
    if(res != 0) printf("write error: res = %d\n", res);

    while(1) {
        //uart_send(uart_recv());
    }
}
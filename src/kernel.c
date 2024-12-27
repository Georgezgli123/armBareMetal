#include "common.h"
#include "mini_uart.h"
#include "printf.h"
#include "irq.h"
#include "utils.h"

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
#if RPI_VERSION == 3
    printf("\tBoard: RPI 3\n");
#elif RPI_VERSION == 4
    printf("\tBoard: RPI 4");
#endif
    printf("\n\nDone, ported printf is using!\n");
    printf("\nException Level: %d\n", get_el());
    while(1) {
        //uart_send(uart_recv());
    }
}
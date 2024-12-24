#include "common.h"
#include "mini_uart.h"

void kernel_main() {
    uart_init();
    uart_send_string("Rasperry PI Bare Metal OS init\n");
#if RPI_VERSION == 3
    uart_send_string("\tBoard: RPI 3\n");
#elif RPI_VERSION == 4
    uart_send_string("\tBoard: RPI 4");
#endif
    uart_send_string("\n\nDone\n");
    while(1) {
        uart_send(uart_recv());
    }
}
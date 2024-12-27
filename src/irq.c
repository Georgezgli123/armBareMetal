#include "utils.h"
#include "printf.h"
#include "entry.h"
#include "peripherals/aux.h"
#include "peripherals/irq.h"
#include "mini_uart.h"
#include "timer.h"

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32"	
};

void show_invalid_entry_message(u32 type, u64 esr, u64 address)
{
	printf("ERROR: %s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}
void enable_interrupt_controller()
 {
    REGS_IRQ->irq0_enable_0 = AUX_IRQ | SYSTEM_TIMER_IRQ_1;
}

void handle_irq() {
    u32 irq;
    irq = REGS_IRQ->irq0_pending_0;

    while(irq) {
        if(irq & AUX_IRQ) {
            irq &= ~AUX_IRQ;
            while((REG_AUX->mu_iir & 4) == 4) {
                printf("UART Recv: ");
                uart_send(uart_recv());
                printf("\n");
            }
        }
		if(irq & SYSTEM_TIMER_IRQ_1) {
			irq &= ~SYSTEM_TIMER_IRQ_1;
			handle_timer_1();
		}
    }
}

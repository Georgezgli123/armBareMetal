#pragma once

#include "peripherals/base.h"
#include "common.h"

enum vc_irqs {
    SYSTEM_TIMER_IRQ_0 = 1,
    SYSTEM_TIMER_IRQ_1 = 2,
    SYSTEM_TIMER_IRQ_2 = 4,
    SYSTEM_TIMER_IRQ_3 = 8,
    AUX_IRQ = (1 << 29)
};

struct arm_irq_regs {
    reg32 irq0_pending_0;
    reg32 irq0_pending_1;
    reg32 irq0_pending_2;
    reg32 reserved0;
    reg32 irq0_enable_0;
    reg32 irq0_enable_1;
    reg32 irq0_enable_2;
    reg32 reserved1;
    reg32 irq0_disable_0;
    reg32 irq0_disable_1;
    reg32 irq0_disable_2;
};

#define REGS_IRQ ((struct arm_irq_regs *)(PBASE + 0x0000B200))
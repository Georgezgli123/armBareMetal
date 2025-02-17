# armBareMetal
This is a project for bare metal to communicate with CPU/peripherals.

## What it has done

* Set up the CPU (ARMv8) running environment, and branch to kernel_main to run the main function, please refer to [boot.S](https://github.com/zhiguoli-32/armBareMetal/blob/main/src/boot.S).
* Implement the GPIO selector to select different functions of GPIO, please refer to [gpio.c](https://github.com/zhiguoli-32/armBareMetal/blob/main/src/gpio.c).
* Implement Interrupt vectors, context switch and irq handler (only for UART and TIMER), please refer to [entry.S](https://github.com/zhiguoli-32/armBareMetal/blob/main/src/entry.S), [irq.S](https://github.com/zhiguoli-32/armBareMetal/blob/main/src/irq.S) and [irq.c](https://github.com/zhiguoli-32/armBareMetal/blob/main/src/irq.c).
* Enable the miniUART (GPIO14-TX,GPIO15-RX Raspberry PI 4), and print out the characters through UART to USB cable on screen, please find the code in [mini_uart.c](https://github.com/zhiguoli-32/armBareMetal/blob/main/src/mini_uart.c).
* Enable timer1, timer3, and timer_spleep, please check [timer.c](https://github.com/zhiguoli-32/armBareMetal/blob/main/src/timer.c)
* Implement I2C (GPIO2-SDA, GPIO3-SCL Raspberry PI 4) and correctly read out a device (ADP8860) ID in kernel.c (line 37 ~44), please check [i2c.c](https://github.com/zhiguoli-32/armBareMetal/blob/main/src/i2c.c) and [kernel.c](https://github.com/zhiguoli-32/armBareMetal/blob/main/src/kernel.c)

## To be done

* Implement SPI driver, and communicate with a display using digit 7 degment module to display something via SPI.
* Implement the HDMI driver to display using videocore mailbox in both DMA and ARM core way, and compare the 2 ways performance.

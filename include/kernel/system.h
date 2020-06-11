#include <stdint.h>

#ifndef _KERNEL_SYSTEM_H
#define _KERNEL_SYSTEM_H

void setup_gdt();
void setup_vga();
void setup_i386();
uint8_t inb(uint16_t _port);
void outb(uint16_t _port, uint8_t _data);
void kernel_main();

#endif
#include <stdint.h>

#ifndef _KERNEL_SYSTEM_H
#define _KERNEL_SYSTEM_H

void setup_gdt();
void setup_i386();
uint8_t inportb(uint16_t _port);
void outportb(uint16_t _port, uint8_t _data);

#endif
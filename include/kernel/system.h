#include <stdint.h>

#ifndef _KERNEL_SYSTEM_H
#define _KERNEL_SYSTEM_H

#define STDIO 1

void setup_gdt();
void setup_idt();
void setup_isrs();
void idt_set_gate(uint8_t num, unsigned long base, uint16_t selector, uint8_t flags);
void setup_vga();
void setup_i386();
uint8_t inb(uint16_t _port);
void outb(uint16_t _port, uint8_t _data);
void kernel_main();

struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};
	

#endif
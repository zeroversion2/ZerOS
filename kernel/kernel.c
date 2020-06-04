#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>
#include <kernel/system.h>

extern void entering_v86(uint32_t ss, uint32_t esp, uint32_t cs, uint32_t eip);

unsigned char inportb(unsigned short _port) {
    unsigned char rv;
    asm volatile("inb %1, %0" : "=a" (rv) : "dN" (_port));
}

void outportb (unsigned short _port, unsigned char _data) {
    asm volatile("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void kernel_main(void) {
    //gdt_install();
    //entering_v86(0,0,0,0);
    terminal_initialize();
    outportb(0x3D4, 14);
    outportb(0x3D5, 0x0);
    outportb(0x3D4, 15);
    outportb(0x3D5, 0x0);
    printf("helo");
}

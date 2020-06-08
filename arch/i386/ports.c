#include <stdint.h>

uint8_t inportb(uint16_t _port) {
    uint8_t rv;
    asm(".intel_syntax noprefix");
    asm volatile("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (uint16_t _port, uint8_t _data) {
    asm volatile("outb %1, %0" : : "dN" (_port), "a" (_data));
}
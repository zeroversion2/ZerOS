#ifndef _KERNEL_SYSTEM_H
#define _KERNEL_SYSTEM_H

void gdt_install();
unsigned char inportb(unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

#endif
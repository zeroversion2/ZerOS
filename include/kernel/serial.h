#ifndef KERNEL_SERIAL_H
#define KERNEL_SERIAL_H

#define PORT 0x3f8

char read_serial();
void write_serial(char c);
void setup_serial();

#endif
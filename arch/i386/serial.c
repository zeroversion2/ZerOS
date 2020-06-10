#include <kernel/system.h>
#include <kernel/serial.h>

int serial_received() {
   return inb(PORT + 5) & 1;
}
 
char read_serial() {
    while (serial_received() == 0);
    char c = inb(PORT);
    if (c == 13) c = 10;
    write_serial(c);
        
    return c;
}

int is_transmit_empty() {
    return inb(PORT + 5) & 0x20;
}

void write_serial(char c) {
    while (is_transmit_empty() == 0);

    outb(PORT,c);
}

void setup_serial() {
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x80);
    outb(PORT + 0, 0x03);
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x03);
    outb(PORT + 2, 0xC7);
    outb(PORT + 4, 0x0B);
}
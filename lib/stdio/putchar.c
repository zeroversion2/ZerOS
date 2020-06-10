#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>

int putchar(int ic) {
    char c = (char) ic;
    //terminal_write(&c, sizeof(c));
    write_serial(c);
    return ic;
}

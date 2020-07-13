#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>
#include <kernel/system.h>

int putchar(int ic) {
    char c = (char) ic;
    #if STDIO == 1
    terminal_write(&c, sizeof(c));
    #elif STDIO == 0
    write_serial(c);
    #endif
    return ic;
}

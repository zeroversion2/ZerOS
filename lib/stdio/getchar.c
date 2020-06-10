#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>

int getchar() {
    int c = (int) read_serial();
    return c;
}

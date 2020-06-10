#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>

int gets() {
    int c = (int) read_serial();
    return c;
}

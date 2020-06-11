#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/serial.h>

char* gets(char* str) {
    char c = 0;
    for (int i = 0; i < strlen(str), c != '\n'; i++) {
        c = read_serial();
        write_serial(c);
        str[i] = c;
    }
    
    return str;
}

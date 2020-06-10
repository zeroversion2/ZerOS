#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <kernel/tty.h>
#include <kernel/system.h>
#include <kernel/serial.h>

void kernel_main(void) {
    setup_i386();
    printf("ls%d\n", '\n');
    char c = getchar();
    printf("%c", c);
}

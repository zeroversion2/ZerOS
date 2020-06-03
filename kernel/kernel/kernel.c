#include <stdio.h>
#include <stdint.h>

#include <kernel/tty.h>

extern void entering_v86(uint32_t ss, uint32_t esp, uint32_t cs, uint32_t eip);

void kernel_main(void) {

    terminal_initialize();
    printf("test");

    // for (int i = 0; i < 28; i++) {
    //     printf("test%c\n", (char)(i + '0'));
    // }
    
    
}

#include <kernel/system.h>
#include <kernel/tty.h>

void setup_i386() {
    setup_gdt();
    terminal_initialize();
}
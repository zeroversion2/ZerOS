#include <kernel/system.h>
#include <kernel/tty.h>
#include <kernel/paging.h>

void setup_i386() {
    terminal_initialize();
    setup_gdt();
    setup_paging();
}
#include <kernel/system.h>
#include <kernel/tty.h>
#include <kernel/paging.h>
#include <kernel/multiboot.h>
#include <stdio.h>

void setup_i386() {
    setup_gdt();
    terminal_initialize();
    setup_serial();
}
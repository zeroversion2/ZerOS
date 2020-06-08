#include <kernel/system.h>
#include <kernel/tty.h>
#include <kernel/paging.h>

void setup_i386() {
    //
    //setup_gdt();
    //setup_paging();
    terminal_initialize();

}
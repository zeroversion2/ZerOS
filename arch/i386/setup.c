#include <kernel/system.h>
#include <kernel/tty.h>
#include <kernel/paging.h>
#include <kernel/multiboot.h>
#include <stdio.h>

void setup_i386(void* bootinfo) {
    struct bootinfo_t* multiboot_info = bootinfo + page_offset;
    setup_serial();
    setup_paging();
    setup_gdt();
    terminal_initialize();
    //setup_vga(multiboot_info);
    
    printf("%x\n", multiboot_info->framebuffer_addr);
    printf("%x\n", multiboot_info->vbe_control_info);
    printf("%d\n", multiboot_info->framebuffer_height);
    printf("%d\n", multiboot_info->framebuffer_width);
    printf("%x\n", multiboot_info->vbe_mode_info);

    printf("%x\n", page_offset);



    kernel_main();
}
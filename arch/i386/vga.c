#include <kernel/system.h>
#include <kernel/multiboot.h>
#include <kernel/paging.h>
#include <kernel/vbe.h>

#include <stdint.h>
#include <stdio.h>

char* vgamem;

void fillrect(unsigned char *vram, unsigned char r, unsigned char g, unsigned   char b, unsigned char w, unsigned char h) {
    unsigned char *where = vram;
    int i, j;
 
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            //putpixel(vram, 64 + j, 64 + i, (r << 16) + (g << 8) + b);
            where[j*4] = r;
            where[j*4 + 1] = g;
            where[j*4 + 2] = b;
        }
        where+=3200;
    }
}

void setup_vga(struct bootinfo_t* multiboot_info) {
    struct vbe_control_info_t* vbe_control_info = multiboot_info->vbe_control_info + page_offset;
    vgamem = (char*) multiboot_info->framebuffer_addr;
    fillrect(vgamem, 0, 255, 255, 200, 200);
    printf("%x\n", sizeof(struct vbe_control_info_t));
    printf("%s\n", vbe_control_info->vbe_signature);
    printf("%x\n", vbe_control_info->oem_string_ptr);
    printf("%c\n", 0x56);
}
#include <kernel/system.h>
#include <kernel/multiboot.h>
#include <kernel/paging.h>
#include <kernel/vbe.h>

#include <stdint.h>
#include <stdio.h>

uint16_t* vgamem;
uint32_t VGA_WIDTH;
uint32_t VGA_HEIGHT;

void fillrect(uint16_t *vram, uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t h) {
    //unsigned char *where = vram;
    int i, j;
 
    for (i = 0; i < w; i++) {
        for (j = 0; j < h; j++) {
            int index = i * VGA_WIDTH + j;
            uint16_t pixel_value = (r << 11) + (g << 5) + (b << 0);
            vram[index] = pixel_value;
        }
    }
}

void setup_vga(struct bootinfo_t* multiboot_info) {
    VGA_WIDTH = multiboot_info->framebuffer_width;
    VGA_HEIGHT = multiboot_info->framebuffer_height;
    struct vbe_control_info_t* vbe_control_info = (void*) multiboot_info->vbe_control_info + page_offset;
    vgamem = (uint16_t*) multiboot_info->framebuffer_addr;
    fillrect(vgamem, 0b11111, 0b111111, 0b11100, 200, 200);
    fillrect(vgamem, 0b11111, 0b111111, 0b11111, 100, 200);
    //vgamem[0] = 0b0000000011111111;

    printf("%x\n", sizeof(struct vbe_control_info_t));
    printf("%s\n", vbe_control_info->vbe_signature);
    printf("%x\n", vbe_control_info->oem_string_ptr);
    printf("%d\n", multiboot_info->framebuffer_type);
    printf("%d\n", multiboot_info->framebuffer_pitch);
    printf("%d\n", multiboot_info->framebuffer_red_field_position);
    printf("%d\n", multiboot_info->framebuffer_red_mask_size);
    printf("%d\n", multiboot_info->framebuffer_green_field_position);
    printf("%d\n", multiboot_info->framebuffer_green_mask_size);
    printf("%d\n", multiboot_info->framebuffer_blue_field_position);
    printf("%d\n", multiboot_info->framebuffer_blue_mask_size);
}
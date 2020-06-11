#include <stdint.h>

#ifndef KERNEL_VBE_H
#define KERNEL_VBE_H

struct vbe_control_info_t {
    char vbe_signature[4];
    uint16_t vbe_version;
    uint32_t oem_string_ptr;
    uint8_t capabilities[4];
    uint32_t video_mode_ptr;
    uint16_t total_memory;
}__attribute__((packed));

#endif
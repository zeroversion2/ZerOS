#include <stdint.h>

#ifndef KERNEL_INCLUDE_MULTIBOOT
#define KERNEL_INCLUDE_MULTIBOOT

struct bootinfo_t {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_higher;
}__attribute__((packed));

#endif
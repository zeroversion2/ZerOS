#include <stdint.h>

void write_eax(uint32_t eax) {
    asm volatile("movl %0, %%eax; hlt" : : "r" (eax));
}

void write_ebx(uint32_t ebx) {
    asm volatile("movl %0, %%ebx; hlt" : : "r" (ebx));
}

void write_ecx(uint32_t ecx) {
    asm volatile("movl %0, %%ecx; hlt" : : "r" (ecx));
}

void write_edx(uint32_t edx) {
    asm volatile("movl %0, %%edx; hlt" : : "r" (edx));
}

void write_esi(uint32_t esi) {
    asm volatile("movl %0, %%esi; hlt" : : "r" (esi));
}

void write_edi(uint32_t edi) {
    asm volatile("movl %0, %%edi; hlt" : : "r" (edi));
}

void halt() {
    asm volatile("hlt");
}
#ifndef _KERNEL_ASM_H
#define _KERNEL_ASM_H

#define PAGE_OFFSET 0xC0000000
#define VGA_OFFSET 0xC0347000

void write_eax(uint32_t eax);
void write_ebx(uint32_t ebx);
void write_ecx(uint32_t ecx);
void write_edx(uint32_t edx);
void write_esi(uint32_t esi);
void write_edi(uint32_t edi);
void halt();

#endif
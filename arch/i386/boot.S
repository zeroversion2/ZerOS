#include <kernel/asm.h>

//multiboot header constants
.set ALIGN,     1<<0
.set MEMINFO,   1<<1
//.set 
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)
//.set gdtr, 0

//multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

//.section .text
//.long gdtr

//setup stack
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384
stack_top:

.section .bss, "aw", @nobits
    .align 4096
boot_page_directory:
    .skip 4096
boot_page_table1:
    .skip 4096

//entry point
.section .text

.global gdt_flush
.extern gp
gdt_flush:
    lgdt (gp)
    movw $0x10,%ax
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%fs
    movw %ax,%gs
    movw %ax,%ss
    ret


.global _start
.type _start, @function
_start:

    //physical address of boot_page_table1
    movl $(boot_page_table1 - PAGE_OFFSET), %edi
    //map address 0
    movl $0, %esi
    movl $1023, %ecx

1:
    //only map the kernel
    cmpl $(_kernel_start - PAGE_OFFSET), %esi
    jl 2f
    cmpl $(_kernel_end - PAGE_OFFSET), %esi
    jge 3f

    //map physical address "present, writable"
    //maps .text and .rodata writable as well
    movl %esi, %edx
    orl $0x003, %edx
    movl %edx, (%edi)

2:
    //size of page
    addl $4096, %esi
    //size of entries in boot_page_table1 is 4 bytes
    addl $4, %edi
    loop 1b

3:
    //map vga video memory to 0xC03FF000 as "present, writable"
    movl $(0x000B8000 | 0x003), boot_page_table1 - PAGE_OFFSET + 1023 * 4

    //map the page table to 0x00000000 and 0xC0000000
    movl $(boot_page_table1 - PAGE_OFFSET + 0x003), boot_page_directory - PAGE_OFFSET + 0
    movl $(boot_page_table1 - PAGE_OFFSET + 0x003), boot_page_directory - PAGE_OFFSET + 768 * 4

    //set cr3 as address of boot_page_directory
    movl $(boot_page_directory - PAGE_OFFSET), %ecx
    movl %ecx, %cr3
    
    //enable paging and the write-protect bit
    movl %cr0, %ecx
    orl $0x80010000, %ecx
    movl %ecx, %cr0

    //jump to higher half
    lea 4f, %ecx
    jmp *%ecx

4:
    //unmap identity mapping
    movl $0, boot_page_directory + 0

    //reload cr0 to force a TLB flush and changes take effect
    movl %cr3, %ecx
    movl %ecx, %cr3

    //set up stack
    mov $stack_top, %esp

    //hlt

    //gdt??????
    // movl 4(%esp), %eax
    // addl $0xc0101000, %eax
    // movl %eax, gdt+2
    // movl 8(%esp), %eax
    // movw %ax, gdt
    // lgdtw gdt

    // hlt

    // movw $0x10, %ax
    // movw %ax, %ds
    // movw %ax, %es
    // movw %ax, %fs
    // movw %ax, %gs
    // movw %ax, %ss
    
    call kernel_main

    cli
1:  hlt
    jmp 1b

.size _start, . - _start

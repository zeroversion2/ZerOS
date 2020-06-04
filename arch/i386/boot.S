[BITS 32]

PAGE_OFFSET equ 0xC0000000
extern kernel_main
extern _kernel_start
extern _kernel_end

;multiboot header
multiboot:
MAGIC dd 0x1BADB002
FLAGS dd 11b
CHECKSUM dd 0x100000000-(0x1BADB002 + 11b)

;setup stack

section .bss alloc write nobits
stack_bottom:
    resb 16384
stack_top:
align 4096
boot_page_directory:
    resb 4096
boot_page_table1:
    resb 4096

;entry point
section .text
global _start
_start:

    mov word [0xb8000], 0x0248
    ;hlt

    ;//physical address of boot_page_table1
    mov edi, (boot_page_table1 - PAGE_OFFSET)
    ;//map address 0
    ;hlt
    mov esi, 0
    mov ecx, 1023

one:
    ;//only map the kernel
    cmp esi, (_kernel_start - PAGE_OFFSET)
    jl two
    cmp esi, (_kernel_end - PAGE_OFFSET)
    jge three

    ;//map physical address "present, writable"
    ;//maps .text and .rodata writable as well
    mov edx, esi
    or edx, 0x003
    mov [edi], edx

two:
    ;//size of page
    add esi, 4096
    ;//size of entries in boot_page_table1 is 4 bytes
    add edi, 4
    loop one

three:
    ;hlt
    ;//map vga video memory to 0xC03FF000 as "present, writable"
    mov eax, 0x000B8000 | 0x003
    mov [boot_page_table1 - PAGE_OFFSET + 1023 * 4], eax

    ;//map the page table to 0x00000000 and 0xC0000000
    mov eax, boot_page_table1 - PAGE_OFFSET + 0x003
    mov [boot_page_directory - PAGE_OFFSET + 0], eax
    mov eax, (boot_page_table1 - PAGE_OFFSET + 0x003)
    mov [boot_page_directory - PAGE_OFFSET + 768 * 4], eax

    ;//set cr3 as address of boot_page_directory
    mov ecx, (boot_page_directory - PAGE_OFFSET)
    mov cr3, ecx
    
    ;//enable paging and the write-protect bit
    mov ecx, cr0
    or ecx, 0x80010000
    mov cr0, ecx
    ;hlt

    ;//jump to higher half
    jmp far [four]

four:
    hlt
    ;//unmap identity mapping
    mov eax, 0x0
    mov [boot_page_directory + 0], eax
    hlt

    ;//reload cr0 to force a TLB flush and changes take effect
    mov ecx, cr3
    mov cr3, ecx

    ;//set up stack
    mov esp, stack_top

;     //hlt

;     //gdt??????
;     // movl 4(%esp), %eax
;     // addl $0xc0101000, %eax
;     // movl %eax, gdt+2
;     // movl 8(%esp), %eax
;     // movw %ax, gdt
;     // lgdtw gdt

;     // hlt

;     // movw $0x10, %ax
;     // movw %ax, %ds
;     // movw %ax, %es
;     // movw %ax, %fs
;     // movw %ax, %gs
;     // movw %ax, %ss
    mov eax, 1
    ;hlt
    call kernel_main
    mov eax, 0

    cli
    q:
    hlt
    jmp q
_end:
size _start _end-_start

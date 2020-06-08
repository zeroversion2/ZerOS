[BITS 32]
MAGIC equ 0x1BADB002
FLAGS equ 11b
CHECKSUM equ -(MAGIC + FLAGS)

PAGE_OFFSET equ 0xC0000000
PAGE_NUMBER equ (PAGE_OFFSET >> 22)

boot_page_directory_p equ boot_page_directory - PAGE_OFFSET
boot_page_table_p equ boot_page_table - PAGE_OFFSET
boot_page_table_pf equ boot_page_table - PAGE_OFFSET

extern kernel_main
extern _kernel_start
extern _kernel_end

section .data
align 0x1000
global boot_page_directory
boot_page_directory:
    dd 0x00000083
    times (PAGE_NUMBER - 1) dd 0
    dd 0x00000083
    times (1024 - PAGE_NUMBER - 1) dd 0
boot_page_table:
    resb 4096

section .bss alloc write nobits
align 4
stack_bottom:
    resb 16384
stack_top:

;entry point
section .text
align 4
multiboot:
dd MAGIC
dd FLAGS
dd CHECKSUM
global _start
_start:

;     ;//set cr3 as address of boot_page_directory
;     mov ecx, boot_page_directory_p
;     mov cr3, ecx

;     mov ecx, cr4
;     or ecx, 0x10
;     mov cr4, ecx
    
;     ;hlt
;     ;//enable paging and the write-protect bit
;     mov ecx, cr0
;     or ecx, 0x80010000
;     mov cr0, ecx
;     ;hlt

;     ;//jump to higher half
;     lea ecx, [higher_half]
;     jmp ecx

; higher_half:
;     ;//unmap identity mapping
;     mov dword [boot_page_directory], 0
;     invlpg [0]
;     ;hlt

    mov eax, boot_page_directory
    hlt

    ;//set up stack
    mov esp, stack_top
    ;hlt

    call kernel_main

    cli
    q:
    hlt
    jmp q
_end:
size _start _end-_start

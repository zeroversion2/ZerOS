[BITS 32]
MAGIC equ 0x1BADB002
FLAGS equ 11b
CHECKSUM equ -(MAGIC + FLAGS)

PAGE_OFFSET equ 0xC0000000
PAGE_NUMBER equ (PAGE_OFFSET >> 22)

page_directory_p equ page_directory - PAGE_OFFSET
page_table1_p equ page_table1 - PAGE_OFFSET

extern kernel_main
extern _kernel_start
extern _kernel_end
extern setup_paging

section .data
align 0x1000
global page_directory
page_directory:
    resb 4096
global page_table1
page_table1:
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
    ;mov eax, page_directory

    xor edx, edx
    mov eax, _kernel_end - PAGE_OFFSET
    mov ebx, 4096
    div ebx
    mov ecx, eax
    ;inc ecx
    ;hlt
    mul ebx
    ;hlt
    fill_table:
    mov eax, ecx
    ;dec eax
    mul ebx
    ;hlt
    or eax, 0x3
    mov dword [page_table1_p + ecx * 4], eax
    ;hlt
    loop fill_table

    mov eax, ecx
    mul ebx
    ;hlt
    or eax, 0x3
    mov dword [page_table1_p + ecx * 4], eax
    mov eax, dword [page_table1_p]
    ;hlt

    mov eax, page_table1_p
    or eax, 0x3
    mov dword [page_directory_p], eax
    mov dword [page_directory_p + 768 * 4], eax
    ;hlt

    ;set cr3 as address of boot_page_directory
    mov ecx, page_directory_p
    ;hlt
    mov cr3, ecx
    
    ;hlt
    ;//enable paging and the write-protect bit
    mov ecx, cr0
    or ecx, 0x80000000
    ;hlt
    mov cr0, ecx
    ;quihlt

    ;//jump to higher half
    lea ecx, [higher_half]
    jmp ecx

higher_half:
    ;//unmap identity mapping
    mov dword [page_directory], 0
    invlpg [0]
    ;hlt

    ;mov eax, boot_page_directory
    ;hlt

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

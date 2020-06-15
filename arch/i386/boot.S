[BITS 32]
extern setup_i386
extern _kernel_start
extern _kernel_end

PAGE_OFFSET equ 0xC0000000
PAGE_NUMBER equ (PAGE_OFFSET >> 22)

page_directory_p equ page_directory - PAGE_OFFSET
page_table1_p equ page_table1 - PAGE_OFFSET

section .data
align 0x1000
global page_directory
page_directory:
    times 1024 dd 0
global page_table1
page_table1:
    times 1024 dd 10b

section .bss alloc write nobits
align 4
stack_bottom:
    resb 16384
stack_top:

P_ALIGN equ 1 << 0
MEMINFO equ 1 << 1
GRAPHICS equ 1 << 2
MAGIC equ 0x1BADB002
FLAGS equ MEMINFO | P_ALIGN | GRAPHICS
CHECKSUM equ -(MAGIC + FLAGS)

GFX_MODE equ 1
GFX_WIDTH equ 640
GFX_HEIGHT equ 480
GFX_DEPTH equ 16

;entry point
section .text
align 4
multiboot:
dd MAGIC
dd FLAGS
dd CHECKSUM
times 5 dd 0
dd GFX_MODE
dd GFX_WIDTH
dd GFX_HEIGHT
dd GFX_DEPTH
global _start
_start:
    ;hlt
    ; add ebx, PAGE_OFFSET
    ; mov [bootinfo_addr], ebx

    ;add entries to page table
    mov esi, _kernel_end - PAGE_OFFSET
    shr esi, 12
    inc esi
    mov ecx, esi
    inc ecx
    fill_table:
    dec ecx
    mov esi, ecx
    shl esi, 12
    or esi, 0x3
    mov dword [page_table1_p + ecx * 4], esi
    cmp ecx, 0
    jge fill_table
    mov eax, dword [page_table1_p]

    ;move page table to directory
    mov eax, page_table1_p
    or eax, 0x3
    mov dword [page_directory_p], eax
    mov dword [page_directory_p + 768 * 4], eax

    ;set cr3 as address of boot_page_directory
    mov ecx, page_directory_p
    mov cr3, ecx
    
    ;enable paging and the write-protect bit
    mov ecx, cr0
    or ecx, 0x80000000
    mov cr0, ecx

    ;jump to higher half
    lea ecx, [higher_half]
    jmp ecx

higher_half:
    ;unmap identity mapping
    mov dword [page_directory], 0
    invlpg [0]

    ;set up stack
    mov esp, stack_top

    push ebx
    call setup_i386

    hlt
_end:
size _start _end-_start

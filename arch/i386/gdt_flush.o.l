     1                                 %line 1+1 arch/i386/gdt_flush.S
     2                                 [section .text]
     3                                 [extern gp]
     4                                 [global gdt_flush]
     5                                 gdt_flush:
     6 00000000 0F0115[00000000]        lgdt [gp]
     7 00000007 66B81000                mov ax, 0x10
     8 0000000B 8ED8                    mov ds, ax
     9 0000000D 8EC0                    mov es, ax
    10 0000000F 8EE0                    mov fs, ax
    11 00000011 8EE8                    mov gs, ax
    12 00000013 8ED0                    mov ss, ax
    13 00000015 C3                      ret

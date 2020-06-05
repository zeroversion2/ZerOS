     1                                 %line 1+1 arch/i386/boot.S
     2                                 [BITS 32]
     3                                 
     4                                 
     5                                 [section .data]
     6                                 PAGE_OFFSET equ 0xC0000000
     7                                 MAGIC equ 0x1BADB002
     8                                 FLAGS equ 11
     9                                 CHECKSUM equ -(MAGIC + FLAGS)
    10                                 
    11                                 [extern kernel_main]
    12                                 [extern _kernel_start]
    13                                 [extern _kernel_end]
    14                                 
    15                                 
    16                                 
    17                                 [section .bss alloc write nobits]
    18                                 stack_bottom:
    19 00000000 <gap>                   resb 16384
    20                                 stack_top:
    21                                 [align 4096]
    22                                 boot_page_directory:
    23 00004000 <gap>                   resb 4096
    24                                 boot_page_table1:
    25 00005000 <gap>                   resb 4096
    26                                 
    27                                 
    28                                 [section .text]
    29                                 multiboot:
    30 00000000 02B0AD1B               dd MAGIC
    31 00000004 03000000               dd FLAGS
    32 00000008 FB4F52E4               dd CHECKSUM
    33                                 [global _start]
    34                                 _start:
    35                                 
    36                                 
    37 0000000C B8[00000000]            mov eax, boot_page_directory
    38                                 
    39                                 
    40                                 
    41 00000011 BF[00000040]            mov edi, (boot_page_table1 - PAGE_OFFSET)
    42                                 
    43                                 
    44 00000016 BE00000000              mov esi, 0
    45 0000001B B9FF030000              mov ecx, 1023
    46                                 
    47                                 one:
    48                                 
    49 00000020 81FE[00000040]          cmp esi, (_kernel_start - PAGE_OFFSET)
    50 00000026 7C0D                    jl two
    51 00000028 81FE[00000040]          cmp esi, (_kernel_end - PAGE_OFFSET)
    52 0000002E 7D10                    jge three
    53                                 
    54                                 
    55                                 
    56 00000030 89F2                    mov edx, esi
    57 00000032 83CA03                  or edx, 0x003
    58 00000035 8917                    mov [edi], edx
    59                                 
    60                                 two:
    61                                 
    62 00000037 81C600100000            add esi, 4096
    63                                 
    64 0000003D 83C704                  add edi, 4
    65 00000040 E2DC                    loop one
    66                                 
    67                                 three:
    68                                 
    69                                 
    70 00000042 B803800B00              mov eax, 0x000B8000 | 0x003
    71 00000047 A3[FC0F0040]            mov [boot_page_table1 - PAGE_OFFSET + 1023 * 4], eax
    72                                 
    73                                 
    74 0000004C B8[03000040]            mov eax, boot_page_table1 - PAGE_OFFSET + 0x003
    75 00000051 A3[00000040]            mov [boot_page_directory - PAGE_OFFSET + 0], eax
    76 00000056 B8[03000040]            mov eax, (boot_page_table1 - PAGE_OFFSET + 0x003)
    77 0000005B A3[000C0040]            mov [boot_page_directory - PAGE_OFFSET + 768 * 4], eax
    78                                 
    79                                 
    80 00000060 B9[00000040]            mov ecx, (boot_page_directory - PAGE_OFFSET)
    81 00000065 0F22D9                  mov cr3, ecx
    82                                 
    83 00000068 F4                      hlt
    84                                 
    85 00000069 0F20C1                  mov ecx, cr0
    86 0000006C 81C900000180            or ecx, 0x80010000
    87 00000072 0F22C1                  mov cr0, ecx
    88                                 
    89                                 
    90                                 
    91 00000075 FF2D[00000000]          jmp far [four]
    92                                 
    93                                 four:
    94 0000007B F4                      hlt
    95                                 
    96 0000007C B800000000              mov eax, 0x0
    97 00000081 A3[00000000]            mov [boot_page_directory + 0], eax
    98 00000086 F4                      hlt
    99                                 
   100                                 
   101 00000087 0F20D9                  mov ecx, cr3
   102 0000008A 0F22D9                  mov cr3, ecx
   103                                 
   104                                 
   105 0000008D BC[00000000]            mov esp, stack_top
   106                                 
   107                                 
   108                                 
   109                                 
   110                                 
   111                                 
   112                                 
   113                                 
   114                                 
   115                                 
   116                                 
   117                                 
   118                                 
   119                                 
   120                                 
   121                                 
   122                                 
   123                                 
   124                                 
   125 00000092 B801000000              mov eax, 1
   126                                 
   127 00000097 E8(F6FFFFFF)            call kernel_main
   128 0000009C B800000000              mov eax, 0
   129                                 
   130 000000A1 FA                      cli
   131                                  q:
   132 000000A2 F4                      hlt
   133 000000A3 EBFB                    jmp q
   134                                 _end:
   135                                 [size _start _end-_start]

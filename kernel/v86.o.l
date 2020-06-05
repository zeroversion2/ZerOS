     1                                 %line 1+1 kernel/v86.S
     2                                 
     3                                 entering_v86:
     4 00000000 89E5                    mov ebp, esp
     5 00000002 FF7504                  push dword [ebp+4]
     6 00000005 FF7508                  push dword [ebp+8]
     7 00000008 9C                      pushfd
     8 00000009 B801000000              mov eax, 1
     9 0000000E C1E011                  shl eax, 17
    10 00000011 090424                  or dword [esp], eax
    11 00000014 FF750C                  push dword [ebp+12]
    12 00000017 FF7510                  push dword [ebp+16]
    13 0000001A CF                      iret

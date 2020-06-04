
entering_v86:
    mov ebp, esp
    push dword [ebp+4]
    push dword [ebp+8]
    pushfd
    mov eax, 1
    shl eax, 17
    or dword [esp], eax
    push dword [ebp+12]
    push dword [ebp+16]
    iret
global set_page_directory
set_page_directory:
    mov eax, [esp+4]
    hlt
    mov cr3, eax
    hlt
    ;ret
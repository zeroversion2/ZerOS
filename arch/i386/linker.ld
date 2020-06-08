ENTRY(_start)

SECTIONS {
    . = 0x100000;

    _kernel_start = .;
    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(COMMON)
        *(.bss)
    }
    _kernel_end = .;
}

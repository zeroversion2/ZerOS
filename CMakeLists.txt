cmake_minimum_required(VERSION 3.16)
project(ZerOS C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_SYSTEM none)
set(CMAKE_SYSTEM_PROCESSOR i686)

set(triple i686-elf)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${triple})

include_directories(include)
include_directories(lib/include)

add_executable(ZerOS
        arch/i386/debug.c
        arch/i386/gdt.c
        arch/i386/idt.c
        arch/i386/isrs.c
        arch/i386/paging.c
        arch/i386/ports.c
        arch/i386/serial.c
        arch/i386/setup.c
        arch/i386/tty.c
        arch/i386/vga.c
        arch/i386/vga.h
        include/kernel/asm.h
        include/kernel/multiboot.h
        include/kernel/paging.h
        include/kernel/serial.h
        include/kernel/system.h
        include/kernel/tty.h
        include/kernel/vbe.h
        kernel/kernel.c
        lib/include/sys/cdefs.h
        lib/include/math.h
        lib/include/stdio.h
        lib/include/stdlib.h
        lib/include/string.h
        lib/stdio/getchar.c
        lib/stdio/gets.c
        lib/stdio/printf.c
        lib/stdio/putchar.c
        lib/stdio/puts.c
        lib/stdlib/abort.c
        lib/stdlib/cast.c
        lib/string/memcmp.c
        lib/string/memcpy.c
        lib/string/memmove.c
        lib/string/memset.c
        lib/string/strlen.c)

target_compile_options(ZerOS PRIVATE -ffreestanding)

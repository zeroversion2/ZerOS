# ZerOS
OS hobby/research project following the osdev wiki. name credit to shippy

Currently supports kernel paging, vga text mode with scrolling and some escape sequences.

To build on linux make sure you have all dependencies installed. For Ubuntu it's build-essential, clang, yasm, grub-pc-bin, and xorriso installed. 'make' should build the kernel and the live ISO, qemu.sh runs it in qemu if you have it installed.

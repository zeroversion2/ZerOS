#!/bin/sh
mkdir -p isodir/boot/grub

cp sysroot/boot/ZerOS.kernel isodir/boot/ZerOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "ZerOS" {
    multiboot /boot/ZerOS.kernel
}
EOF
grub-mkrescue -o ZerOS.iso isodir

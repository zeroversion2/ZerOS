#!/bin/sh
mkdir -p isodir/boot/grub

cp sysroot/boot/ZerOS.kernel isodir/boot/ZerOS.kernel
cp ./grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o ZerOS.iso isodir

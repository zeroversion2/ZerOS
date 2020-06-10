#!/bin/sh
qemu-system-i386 -accel kvm -cdrom ZerOS.iso -nographic
printf "\n"
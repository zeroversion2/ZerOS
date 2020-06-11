#!/bin/sh
qemu-system-i386 -accel kvm -cdrom ZerOS.iso -serial stdio
printf "\n"
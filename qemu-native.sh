#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST).exe -accel whpx -display sdl -kernel sysroot/boot/os.kernel

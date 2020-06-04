#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel sysroot/boot/ZerOS.kernel -monitor stdio
printf "\n"
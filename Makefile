PREFIX:=/usr
EXEC_PREFIX:=$(PREFIX)
BOOTDIR:=/boot
LIBDIR:=$(EXEC_PREFIX)/lib
INCLUDEDIR:=$(PREFIX)/include

SYSROOT:=$(PWD)/sysroot

DEFAULT_HOST:=i686-elf
HOST:=$(DEFAULT_HOST)
HOSTARCH:=i386

COMPILER_PREFIX:=$(HOME)/opt/cross/bin/$(HOST)

AR:=$(COMPILER_PREFIX)-ar
AS:=yasm -Worphan-labels -f elf32
CC:=clang --target=i686-elf

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=$(SYSROOT)
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS+=--sysroot=$(SYSROOT) -isystem=$(INCLUDEDIR) -ffreestanding -Wall -Wextra
CPPFLAGS+=-D__is_kernel -Iinclude -Ilib/include
LDFLAGS+=
LIBS+=-nostdlib

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/Makefile
include ./lib/Makefile

CFLAGS+=$(KERNEL_ARCH_CFLAGS)
CPPFLAGS+=$(KERNEL_ARCH_CPPFLAGS)
LDFLAGS+=$(KERNEL_ARCH_LDFLAGS)
LIBS+=$(KERNEL_ARCH_LIBS)
 
KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o
			  
OBJS=\
$(FREEOBJS) \
$(KERNEL_OBJS) \
	   
LINK_LIST=\
$(KERNEL_OBJS) \
$(FREEOBJS) \
$(LIBS) \

.PHONY: all clean install-headers install-kernel
.SUFFIXES: .o .c .S

all: ZerOS.iso

ZerOS.iso: ZerOS.kernel install-kernel
	mkdir -p isodir/boot/grub
	cp sysroot/boot/ZerOS.kernel isodir/boot/ZerOS.kernel
	cp ./grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ZerOS.iso isodir

ZerOS.kernel: install-headers $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LDFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot ZerOS.kernel

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(AS) $< -o $@

clean:
	rm -f ZerOS.kernel
	rm -rf sysroot
	rm -rf isodir
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d
	rm -f $(OBJS:.o=.o.l) *.l */*.l */*/*.l

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.
	cp -R --preserve=timestamps lib/include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: ZerOS.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp ZerOS.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)

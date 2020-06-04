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
#AS:=$(COMPILER_PREFIX)-gcc
#CC:=clang --target=i686-elf
CC:=$(COMPILER_PREFIX)-gcc

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
CPPFLAGS+=-D__is_kernel -Iinclude
LDFLAGS+=
LIBS+=-nostdlib

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/Makefile
include ./lib/Makefile

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)
 
KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/v86.o \
kernel/kernel.o
			  
OBJS=\
$(FREEOBJS) \
$(KERNEL_OBJS) \
	   
LINK_LIST=\
$(LDFLAGS) \
$(KERNEL_OBJS) \
$(FREEOBJS) \
$(LIBS) \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: install-headers ZerOS.kernel

ZerOS.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot ZerOS.kernel

# $(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
# 	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(AS) $< -o $@ -l $@.l

clean:
	rm -f ZerOS.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d
	rm -f $(OBJS:.o=.o.l) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.
	cp -R --preserve=timestamps lib/include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: ZerOS.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp ZerOS.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)

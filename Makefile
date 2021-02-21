TOOLCHAIN_PREFIX = m68k-elf-

VPATH = src

# boot.o should be the first on the list (linker script / entry point)
OBJECTS =	obj/boot.o

# order of other objects doesn't matter
OBJECTS +=	obj/blitter.o obj/command.o obj/fd.o obj/kernel.o obj/kernel_asm.o \
		obj/init.o obj/mon.o obj/sids.o obj/timer.o \
		obj/timer_asm.o obj/tty.o obj/vicv.o obj/vicv_asm.o

# libc objects
OBJECTS +=	obj/libc/allocation.o obj/libc/exit.o obj/libc/memcpy.o \
		obj/libc/memset.o obj/libc/printf.o obj/libc/putchar.o obj/libc/puts.o obj/libc/strlen.o \
		obj/libc/strchr.o obj/libc/strcmp.o obj/libc/strtok.o

# lox objects
OBJECTS +=	obj/lox/chunk.o obj/lox/debug.o obj/lox/lox.o obj/lox/memory.o

CC = $(TOOLCHAIN_PREFIX)gcc

# -fleading-underscore makes it linkable under linux (or something to do with elf????)
# -O0 and -O1 seem to work, -O2 and -O3 cause problems
CFLAGS =	-fleading-underscore \
		-nostdlib \
		-mshort \
		-m68000 \
		-fomit-frame-pointer \
		-Wall -Wextra -c -O2 \
		-lgcc \
		-ffreestanding \
		-Isrc/libc \
		-Isrc

LD = $(TOOLCHAIN_PREFIX)ld

LDFLAGS = -T kernel.ld -Map=kernel.map

CCNATIVE = gcc

all: kernel.bin

kernel.bin: kernel_unpatched.bin mk_kernel
	./mk_kernel

kernel_unpatched.bin: $(OBJECTS) kernel.ld
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel_unpatched.bin

obj/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

obj/%.o: %.S
	$(CC) $(CFLAGS) $< -o $@

mk_kernel: tools/mk_kernel.c tools/cbm_cp437_font.c
	$(CCNATIVE) -o mk_kernel tools/mk_kernel.c tools/cbm_cp437_font.c

#lox: src/lox/main.c src/lox/chunk.c src/lox/memory.c
# 	$(CCNATIVE) -o lox src/lox/main.c src/lox/chunk.c src/lox/memory.c

clean:
	rm kernel.cpp kernel.bin kernel_unpatched.bin kernel.map mk_kernel $(OBJECTS)

TOOLCHAIN_PREFIX = m68k-elf-

VPATH = src

# boot.o should be the first on the list (linker script / entry point)
OBJECTS =	obj/boot.o

# order of other objects doesn't matter
OBJECTS +=	obj/blitter.o obj/command.o obj/fd.o obj/kernel.o obj/kernel_asm.o \
		obj/init.o obj/mon.o obj/sids.o obj/string.o obj/timer.o \
		obj/timer_asm.o obj/tty.o obj/vicv.o obj/vicv_asm.o

# libc objects
OBJECTS +=	obj/libc/malloc.o obj/libc/memcpy.o obj/libc/memset.o obj/libc/strlen.o

# lox objects
# OBJECTS +=	obj/lox/chunk.o obj/lox/lox.o obj/lox/memory.o

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

LDFLAGS = -T rom.ld -Map=rom.map

CCNATIVE = gcc

all: rom.bin lox

rom.bin: rom_unpatched.bin mk_rom
	./mk_rom

rom_unpatched.bin: $(OBJECTS) rom.ld
	$(LD) $(LDFLAGS) $(OBJECTS) -o rom_unpatched.bin

obj/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

obj/%.o: %.S
	$(CC) $(CFLAGS) $< -o $@

mk_rom: tools/mk_rom.c tools/cbm_cp437_font.c
	$(CCNATIVE) -o mk_rom tools/mk_rom.c tools/cbm_cp437_font.c

lox: src/lox/main.c src/lox/chunk.c src/lox/memory.c
	$(CCNATIVE) -o lox src/lox/main.c src/lox/chunk.c src/lox/memory.c

clean:
	rm rom.cpp rom.bin rom_unpatched.bin rom.map mk_rom lox $(OBJECTS)

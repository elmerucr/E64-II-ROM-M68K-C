# change to 1 if using m68k-elf-gcc
ELF = 0

ifeq (1,$(ELF))
# Standard ELF toolchain
TOOLCHAIN_PREFIX = m68k-elf-
else
# MiNT toolchain
TOOLCHAIN_PREFIX = m68k-atari-mint-
endif


OBJECTS = boot.o kmain.o
CC = $(TOOLCHAIN_PREFIX)gcc
# -fleading-underscore makes it linkable under linux (or something to do with elf????)
CFLAGS = -fleading-underscore -nostdlib -mshort -m68000 -fomit-frame-pointer -Wall -Wextra -c
LD = $(TOOLCHAIN_PREFIX)ld
LDFLAGS = -T kernel.ld -Map=kernel.map

CCNATIVE = gcc

all: kernel.bin pad

kernel.bin: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) $< -o $@

pad: pad.c
	$(CCNATIVE) -o pad pad.c

clean:
	rm *.o
	rm kernel.bin
	rm kernel.map
	rm pad

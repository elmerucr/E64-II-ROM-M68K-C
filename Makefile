# change to 1 if using m68k-elf-gcc
ELF = 0

ifeq (1,$(ELF))
# Standard ELF toolchain
TOOLCHAIN_PREFIX = m68k-elf-
else
# MiNT toolchain
TOOLCHAIN_PREFIX = m68k-atari-mint-
endif

SOURCES_PREFIX = src

OBJECTS =	boot.o \
			kinit.o \
			kmain.o
CC = $(TOOLCHAIN_PREFIX)gcc
# -fleading-underscore makes it linkable under linux (or something to do with elf????)
CFLAGS =	-fleading-underscore \
			-nostdlib \
			-mshort \
			-m68000 \
			-fomit-frame-pointer \
			-Wall -Wextra -c
LD = $(TOOLCHAIN_PREFIX)ld
LDFLAGS = -T kernel.ld -Map=kernel.map

CCNATIVE = gcc

all: kernel.bin

kernel.bin: unpatched_kernel.bin mk_kernel
	./mk_kernel

unpatched_kernel.bin: $(OBJECTS) kernel.ld
	$(LD) $(LDFLAGS) $(OBJECTS) -o unpatched_kernel.bin

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) $< -o $@

mk_kernel: mk_kernel.c
	$(CCNATIVE) -o mk_kernel mk_kernel.c

clean:
	rm kernel.cpp kernel.bin unpatched_kernel.bin kernel.map mk_kernel $(OBJECTS)

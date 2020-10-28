TOOLCHAIN_PREFIX = m68k-elf-

# boot.o should be the first on the list (linker script / entry point)
OBJECTS =	boot.o \
			kernel.o \
			kernel_asm.o \
			init.o \
			kmain.o \
			vicv.o

CC = $(TOOLCHAIN_PREFIX)gcc

# -fleading-underscore makes it linkable under linux (or something to do with elf????)
# -O0 and -O1 seem to work, -O2 and -O3 cause problems
CFLAGS =	-fleading-underscore \
			-nostdlib \
			-mshort \
			-m68000 \
			-fomit-frame-pointer \
			-Wall -Wextra -c -O1 \
			-lgcc \
			-ffreestanding
LD = $(TOOLCHAIN_PREFIX)ld
LDFLAGS = -T rom.ld -Map=rom.map

CCNATIVE = gcc

all: rom.bin

rom.bin: rom_unpatched.bin mk_rom
	./mk_rom

rom_unpatched.bin: $(OBJECTS) rom.ld
	$(LD) $(LDFLAGS) $(OBJECTS) -o rom_unpatched.bin

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) $< -o $@

mk_rom: mk_rom.c
	$(CCNATIVE) -o mk_rom mk_rom.c

clean:
	rm rom.cpp rom.bin rom_unpatched.bin rom.map mk_rom $(OBJECTS)

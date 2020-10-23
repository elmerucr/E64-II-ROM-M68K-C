# E64-II-rom
## Introduction
[E64-II](https://github.com/elmerucr/E64-II) is a virtual computer system that runs on macOS and linux. It's mainly inspired by the Commodore 64 but implements significant parts of Amiga 500 and Atari ST technology as well.
The software in this repository forms the ROM & Kernel of E64-II.
## Building
Make sure you have either `m68k-elf-as` and `m68k-elf-gcc` or `m68k-atari-mint-as` and `m68k-atari-mint-gcc` installed. The former can be build from sources with good instructions from [here](https://wiki.osdev.org/GCC_Cross-Compiler). The latter can be downloaded from [here](http://vincent.riviere.free.fr/soft/m68k-atari-mint/). In the root directory there is a `Makefile`, so run with `make`. Use command `make ELF=1` when `m68k-elf-...` is in use. The final product will be a `rom.bin` file of exactly 65536 bytes. To use this rom in stead of the standard rom delivered with `E64-II`, just copy it in the `$HOME/.E64-II/` settings directory.
## Links
* [EmuTOS](https://github.com/emutos/emutos) - Free operating system for Atari computers, and more.
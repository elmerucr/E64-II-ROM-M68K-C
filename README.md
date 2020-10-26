# E64-II-ROM
## Introduction
[E64-II](https://github.com/elmerucr/E64-II) is a virtual computer system that runs on macOS and linux. It's mainly inspired by the Commodore 64 but implements significant parts of Amiga 500 and Atari ST technology as well.
The software in this repository forms the ROM & Kernel of E64-II.
## Building
Make sure you have `m68k-elf-as` and `m68k-elf-gcc` available from the command line. Good instructions can be found [here](https://wiki.osdev.org/GCC_Cross-Compiler). The final products after running `make` will be a `rom.bin` file of exactly 65536 bytes and a `rom.cpp` source file. To use the `rom.bin` in stead of the standard rom delivered with `E64-II` copy it in the `$HOME/.E64-II/` settings directory.
## Links
* [E64-II](https://github.com/elmerucr/E64-II) - A virtual computer system that runs on macOS and Linux.
* [EmuTOS](https://github.com/emutos/emutos) - Free operating system for Atari computers, and more.
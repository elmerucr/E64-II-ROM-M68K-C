# E64-II-KERNEL
![E64](./docs/E64-II_icon.png)
## Introduction
[E64-II](https://github.com/elmerucr/E64-II) is a virtual computer system that runs on macOS and linux. It's mainly inspired by the Commodore 64 but implements significant parts of Amiga 500 and Atari ST technology as well. Without any software inside this virtual machine, it wouldn't do much and the software in this repository forms the KERNEL of E64-II.
## Building
Make sure `m68k-elf-as` and `m68k-elf-gcc` are available from the command line. Building instructions can be found [here](https://wiki.osdev.org/GCC_Cross-Compiler). The final products after running `make` will be a `rom.bin` file (64kb) and a `rom.cpp` source file. To use the `rom.bin` instead of the standard rom delivered with `E64-II`, copy it in the `$HOME/.E64-II/` settings directory.
## Links
* [E64-II](https://github.com/elmerucr/E64-II) - A virtual computer system that runs on macOS and Linux.
* [EmuTOS](https://github.com/emutos/emutos) - Free operating system for Atari computers, and more.
* [OSDev.org](https://wiki.osdev.org/Main_Page) - Website about the creation of operating systems.

#ifndef KERNEL_H
#define KERNEL_H

#define IO_BASE_ADDRESS     0x00fb0000

#define VICV_BASE_ADDRESS   (IO_BASE_ADDRESS+0x0400)
#define	VICV_BORDER_COLOR	(VICV_BASE_ADDRESS+0x00)
#define VICV_BORDER_SIZE	(VICV_BASE_ADDRESS+0x0c)

void kinit(void);
void kmain(void);

// poke & peek functionality
void kpokeb(unsigned long address, unsigned char byte);
void kpokew(unsigned long address, unsigned int  word);
void kpokel(unsigned long address, unsigned long lwrd);
unsigned char kpeekb(unsigned long address);
unsigned int  kpeekw(unsigned long address);
unsigned long kpeekl(unsigned long address);

#endif

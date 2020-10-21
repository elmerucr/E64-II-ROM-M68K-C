#ifndef KERNEL_H
#define KERNEL_H

#define	VICV_BORDER_COLOR	0x00ff0400
#define VICV_BORDER_SIZE	0x00ff040C

extern unsigned char *cbm_cp437_font;

void kinit(void);
void kmain(void);

/*  poke & peek functionalities
 *
 */
void kpokeb(unsigned long address, unsigned char byte);
void kpokew(unsigned long address, unsigned int  word);
void kpokel(unsigned long address, unsigned long lwrd);
unsigned char kpeekb(unsigned char *address);
unsigned char kpeekw(unsigned int  *address);
unsigned char kpeekl(unsigned long *address);

#endif

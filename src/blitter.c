#include "blitter.h"
#include "kernel.h"

#include <stdlib.h>

#define MAX_BLITS   256

void **blitter_list;
u8 available;

void blitter_init()
{
	available = 0;
	blitter_list = malloc(MAX_BLITS * sizeof(void *));
	for (int i=0; i<MAX_BLITS; i++)
		blitter_list[i] = (void *)0x00000000;

	blitter_list[0] = (void *)0x80000000;	// clear buffer
	available += 1;
}

void blitter_add_action(void *action)
{
	blitter_list[available] = action;
	available++;
}

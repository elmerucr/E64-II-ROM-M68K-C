#include "definitions.h"

	.globl  _vicv_vblank_exception_handler

	.text

_vicv_vblank_exception_handler:

	movel	%a0,%sp@-
	moveb   #1,VICV_ISR		| acknowledge interrupt
	moveb   #1,VICV_BUFFERSWAP
	moveal  _blitter_list,%a0
1: 	movel   %a0@+,BLITTER_DATA
	beq     2f
	moveb   #1,BLITTER_CONTROL
	bra     1b
2: 	movel   %sp@+,%a0
	rte

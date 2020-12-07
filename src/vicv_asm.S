#include "definitions.h"

	.globl  _vicv_vblank_exception_handler

	.text

_vicv_vblank_exception_handler:

	moveml	%a0-%a2/%d0-%d2,%sp@-	| save regs
	moveb   #1,VICV_ISR		| acknowledge interrupt
	moveb   #1,VICV_BUFFERSWAP
	moveal  _blitter_list,%a0
1: 	movel   %a0@+,BLITTER_DATA
	beq     2f
	moveb   #1,BLITTER_CONTROL
	bra     1b
2:	moveml   %sp@+,%a0-%a2/%d0-%d2	| restore regs
	rte

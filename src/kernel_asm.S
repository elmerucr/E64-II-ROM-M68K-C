#include "definitions.h"

	.globl	_address_error_exception_handler
	.globl	_disable_interrupts
	.globl	_restore_interrupts

	.text

_address_error_exception_handler:
	movew	#C64_BLACK,VICV_HOR_BORDER_COLOR
1:	addq	#1,VICV_HOR_BORDER_SIZE
	bra	1b

_disable_interrupts:
	movew	%sr,store_sr
	oriw	#0x0700,%sr
	rts

_restore_interrupts:
	movew	store_sr,%sr
	rts


	.bss

store_sr:
	dsw	1

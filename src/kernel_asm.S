#include "definitions.h"

	.globl	_address_error_exception_handler

	.text

_address_error_exception_handler:

	movew	#C64_BLUE,VICV_HOR_BORDER_COLOR
1:	addq	#1,VICV_HOR_BORDER_SIZE
	bra	1b

#include "definitions.h"

	.text

	dcl	INITIAL_SSP	| superv stackp (at 0x000000 in E64-II)
	dcl	boot		| initial progr counter (at 0x000004 in E64-II)

boot:
	movew	#0x2700,%sr	| disable all interrupts (not necessary on cold
				| boot, matters for software reset)
	jmp	_init

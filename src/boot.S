#include "definitions.h"

	.text

	dc.l	INITIAL_SSP	| supervisor stackpointer (at 0x000000 in E64-II)
	dc.l	boot		| initial program counter (at 0x000004 in E64-II)

boot:
	movew	#0x2700,%sr	| disable all interrupts (not necessary on cold
				| boot, matters for software reset)
	jmp	_init

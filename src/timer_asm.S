#include "definitions.h"

	.globl  _timer_exception_handler

	.globl	_timer0_vector
	.globl	_timer1_vector
	.globl	_timer2_vector
	.globl	_timer3_vector

	.data

_timer0_vector:
	dcl	_timer_handler_dummy
_timer1_vector:
	dcl	_timer_handler_dummy
_timer2_vector:
	dcl	_timer_handler_dummy
_timer3_vector:
	dcl	_timer_handler_dummy


	.text

_timer_exception_handler:
	btst	#0,TIMER_STATUS_REGISTER
	beq	1f
	moveb	#0b00000001,TIMER_STATUS_REGISTER
	moveal	_timer0_vector,%a0
	jsr	%a0@
1:	btst	#1,TIMER_STATUS_REGISTER
	beq	2f
	moveb	#0b00000010,TIMER_STATUS_REGISTER
	moveal	_timer1_vector,%a0
	jsr	%a0@
2:	btst	#2,TIMER_STATUS_REGISTER
	beq	3f
	moveb	#0b00000100,TIMER_STATUS_REGISTER
	moveal	_timer2_vector,%a0
	jsr	%a0@
3:	btst	#3,TIMER_STATUS_REGISTER
	beq	4f
	moveb	#0b00001000,TIMER_STATUS_REGISTER
	moveal	_timer3_vector,%a0
	jsr	%a0@
4:	rte

_timer_handler_dummy:
	rts

#include "definitions.h"

	.globl  _timer_exception_handler

	.globl	_timer0_vector
	.globl	_timer1_vector
	.globl	_timer2_vector
	.globl	_timer3_vector
	.globl	_timer4_vector
	.globl	_timer5_vector
	.globl	_timer6_vector
	.globl	_timer7_vector

	.data

_timer0_vector:
	dcl	_timer_handler_dummy
_timer1_vector:
	dcl	_timer_handler_dummy
_timer2_vector:
	dcl	_timer_handler_dummy
_timer3_vector:
	dcl	_timer_handler_dummy
_timer4_vector:
	dcl	_timer_handler_dummy
_timer5_vector:
	dcl	_timer_handler_dummy
_timer6_vector:
	dcl	_timer_handler_dummy
_timer7_vector:
	dcl	_timer_handler_dummy


	.text

_timer_exception_handler:
	moveml	%a0-%a2/%d0-%d2,%sp@-			| save regs
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
4:	btst	#4,TIMER_STATUS_REGISTER
	beq	5f
	moveb	#0b00010000,TIMER_STATUS_REGISTER
	moveal	_timer4_vector,%a0
	jsr	%a0@
5:	btst	#5,TIMER_STATUS_REGISTER
	beq	6f
	moveb	#0b00100000,TIMER_STATUS_REGISTER
	moveal	_timer5_vector,%a0
	jsr	%a0@
6:	btst	#6,TIMER_STATUS_REGISTER
	beq	7f
	moveb	#0b01000000,TIMER_STATUS_REGISTER
	moveal	_timer6_vector,%a0
	jsr	%a0@
7:	btst	#7,TIMER_STATUS_REGISTER
	beq	8f
	moveb	#0b10000000,TIMER_STATUS_REGISTER
	moveal	_timer7_vector,%a0
	jsr	%a0@
8:	moveml   %sp@+,%a0-%a2/%d0-%d2			| restore regs
	rte

_timer_handler_dummy:
	rts

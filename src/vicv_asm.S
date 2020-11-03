#include "definitions.h"

    .globl  _vicv_vblank_exception_handler

    .text

_vicv_vblank_exception_handler:

    movel	%a0,%sp@-           // save a0
    moveb   #1,VICV_ISR         // acknowledge interrupt
    moveb   #1,VICV_BUFFERSWAP  // swap front and backbuffers
    moveb   #1,BLITTER_CONTROL	// clear the backbuffer
    moveal  _blitter_list,%a0
1:  movel   %a0@+,BLITTER_DATA_32_BIT
    beq     2f
    moveb   #2,BLITTER_CONTROL
    bra     1b
2:  movel   %sp@+,%a0           // restore a0
    rte                         // return from exception

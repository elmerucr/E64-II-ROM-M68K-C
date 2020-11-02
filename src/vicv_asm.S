#include "definitions.h"

    .globl  _vicv_vblank_exception_handler

    .text

_vicv_vblank_exception_handler:

    moveb   #1,VICV_ISR         // acknowledge interrupt
    moveb   #1,VICV_BUFFERSWAP  // swap front and backbuffers
    moveb   #1,BLITTER_CONTROL	// clear the backbuffer
    rte                         // return from exception (so don't use rts)

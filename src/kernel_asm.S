#include "definitions.h"

    .globl  _address_error_exception_handler

    .text

_address_error_exception_handler:

    movew   #C64_BLUE,VICV_BORDER_COLOR
    movew   #C64_LIGHTBLUE,VICV_BORDER_COLOR
    moveb   #80,VICV_BORDER_SIZE
    bra     _address_error_exception_handler

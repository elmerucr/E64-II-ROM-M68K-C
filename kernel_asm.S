    .globl  _set_interrupt_priority_mask

_set_interrupt_priority_mask:
    clrw    %d0
    moveb   %sp@(5),%d0         // get value from stack
    andib   #7,%d0              // make sure maximum value is 7 (this may not be a good solution!)
    lslw    #8,%d0              // multiply by 256
    movew   %sr,%d1
    andiw   #0xf8ff,%d1
    orw     %d0,%d1
    movew   %d1,%sr
    rts

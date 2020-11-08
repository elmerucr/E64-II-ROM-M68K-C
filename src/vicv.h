#ifndef VICV_H
#define VICV_H

struct __attribute__((packed)) vicv_ic {
};

extern struct vicv_ic vicv;

void vicv_vblank_exception_handler();

#endif

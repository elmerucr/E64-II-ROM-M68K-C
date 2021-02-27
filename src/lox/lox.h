#ifndef LOX_H
#define LOX_H

#include "common.h"
#include "chunk.h"
#include "debug.h"

void lox_init();
void lox_cleanup();

char *lox_prompt();
void lox_interprete(char *line);

#endif

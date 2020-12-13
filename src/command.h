#include "kernel.h"

#ifndef COMMAND_H
#define COMMAND_H

struct command_env {
	//
};

extern struct command_env command;

void command_init();
void command_interprete_line(char *line);
void command_prompt();

#endif

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

void command_go();

bool hex_string_to_int(const char *temp_string, u32 *return_value);

#endif

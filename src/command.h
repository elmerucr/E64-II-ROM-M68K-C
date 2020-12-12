#include "kernel.h"
#include <stdbool.h>

#ifndef COMMAND_H
#define COMMAND_H

struct command_env {
	//
};

extern struct command_env command;

void command_init();
void command_interprete_line(char *line);
void command_prompt();
char *command_strtok(char *s, char *delim);
int command_strcmp(const char * str1, const char * str2);

#endif

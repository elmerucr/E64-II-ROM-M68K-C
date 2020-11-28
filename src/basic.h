#ifndef BASIC_H
#define BASIC_H

enum basic_mode {
	DIRECT,
	RUNNING
};

struct basic_env {
	enum basic_mode current_mode;
	void *start_of_text;
	void *end_of_text;
	void *start_of_vars;
	void *end_of_vars;
};

void basic_cold_start();
void basic_warm_start();
void basic_interprete(char *line);

#endif

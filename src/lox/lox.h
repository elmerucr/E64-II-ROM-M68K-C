#ifndef LOX_H
#define LOX_H

void lox_init();
void lox_cleanup();

char *lox_prompt();
void lox_interprete_line(char *line);

#endif

#include "string.h"
#include <stdbool.h>
#include <stddef.h>

/*
 * https://gist.github.com/sushlala/3172c37f2947e96977b6a0682ec55a60
 */
bool is_delim(char c, char *delim)
{
	while (*delim != '\0') {
		if (c == *delim)
			return true;
		delim++;
	}
	return false;
}

/*
 * https://gist.github.com/sushlala/3172c37f2947e96977b6a0682ec55a60
 */
char *strtok(char *s, char *delim) {
	static char *p; // start of the next search
	if (!s) {
		s = p;
	}
	if (!s) {
		// user is bad user
		return NULL;
	}

	// handle beginning of the string containing delims
	while (1) {
		if (is_delim(*s, delim)) {
			s++;
			continue;
		}
		if (*s == '\0') {
			return NULL; // we've reached the end of the string
		}
		// now, we've hit a regular character. Let's exit the
		// loop, and we'd need to give the caller a string
		// that starts here.
		break;
  	}

	char *ret = s;
	while (1) {
		if (*s == '\0') {
			p = s; // next exec will return NULL
			return ret;
		}
		if (is_delim(*s, delim)) {
			*s = '\0';
			p = s + 1;
			return ret;
		}
		s++;
	}
}

/*
 * https://stackoverflow.com/questions/20004458/optimized-strcmp-implementation
 */
int strcmp(const char * str1, const char * str2)
{
	while (*str1 && (*str1 == *str2))
		str1++, str2++;
	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

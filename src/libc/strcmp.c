/*
 * strcmp.c
 */

#include <string.h>

int strcmp(const char *s1, const char *s2)
{
	const unsigned char *c1 = (const unsigned char *)s1;
	const unsigned char *c2 = (const unsigned char *)s2;
	unsigned char ch;
	int d = 0;

	while (1) {
		d = (int)(ch = *c1++) - (int)*c2++;
		if (d || !ch)
			break;
	}

	return d;
}

// /*
//  * https://stackoverflow.com/questions/20004458/optimized-strcmp-implementation
//  */
// int strcmp(const char * str1, const char * str2)
// {
// 	while (*str1 && (*str1 == *str2))
// 		str1++, str2++;
// 	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
// }

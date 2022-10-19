#include "main.h"

/**
 * get_size - checks and calculates the size to cast the arguments
 * @format: formatted string literal in which to print
 * @len: length of arguments to be printed
 * 
 * Return: size
 */

int get_size(const char *format, int *len)
{
	int i = *len + 1;
	int size = 0;

	if (format[i] == 'l')
		size = LONG_S;
	else if (format[i] == 'h')
		size = SHORT_S;

	if (size == 0)
		*len = i - 1;
	else
		*len = i;

	return (size);
}


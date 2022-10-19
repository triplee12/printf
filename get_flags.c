#include "main.h"

/**
 * get_flags - checks active flags
 * @format: formatted string literal in which to print the argument
 * @len: length of argument (can takes an argument)
 *
 * Return: flags
 */

int get_flags(const char *format, int *len)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8 16 */
	int i , j;
	int flags = 0;
	const char F_CHAR[] = {'-', '+', '#', ' ', '\0'};
	const int F_ARR[] = {FLAG_MINUS, FLAG_PLUS, FLAG_ZERO, FLAG_HASH, FLAG_SPACE, 0};

	for (i = *len + 1; format[i] != '\0'; i++)
	{
		for (j = 0; F_CHAR[j] != '\0'; j++)
			if (format[i] == F_CHAR[j])
			{
				flags |= F_ARR[j];
				break;
			}

		if (F_CHAR[j] == 0)
			break;
	}

	*len = i - 1;

	return (flags);
}


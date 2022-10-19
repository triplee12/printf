#include "main.h"

/**
 * get_width - checks and calculates the width for printing
 * @format: formatted string literal in which to print
 * @args: list of arguments to be printed
 * @len: length of arguments
 *
 * Return: width
 */

int get_width(const char *format, int *len, va_list args)
{
	int curr_i;
	int width = 0;

	for (curr_i = *len + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*len = curr_i - 1;

	return (width);
}


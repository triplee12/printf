#include "main.h"

/**
 * get_precision - checks and calculates the precision for printing
 * @format: formatted string literal in which to print the arguments
 * @len: length of arguments to be printed
 * @args: list of argurments
 *
 * Return: precision
 */

int get_precision(const char *format, int *len, va_list args)
{
	int i = *len + 1;
	int precision = -1;

	if (format[i] != '.')
		return (precision);

	precision = 0;

	for (i += 1; format[i] != '\0'; i++)
	{
		if (is_digit(format[i]))
		{
			precision *= 10;
			precision += format[i] - '0';
		}
		else if (format[i] == '*')
		{
			i++;
			precision = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*len = i - 1;

	return (precision);
}


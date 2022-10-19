#include "main.h"

void print_buff(char buffer[], int *indx);

/**
 * _printf - prints all formatted characters
 * @format: format specifier
 *
 * Return: number of printed characters
 */

int _printf(const char *format, ...)
{
	int i, printed = 0, printed_ch = 0;
	int flags, width, precision, size, indx = 0;
	va_list args;
	char buffer[BUFFER_S];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[indx++] = format[i];
			if (indx == BUFFER_S)
				print_buff(buffer, &indx);
			printed_ch++;
		}
		else
		{
			print_buff(buffer, &indx);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, args, buffer, flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_ch += printed;
		}
	}

	print_buff(buffer, &indx);

	va_end(args);

	return (printed_ch);
}

/**
 * print_buff - prints contents in the buffer if exists
 * @buffer: array of characters
 * indx: index at which to add next character
 *
 * Return: nothing
 */

void print_buff(char buffer[], int *indx)
{
	if (*indx > 0)
		write(1, &buffer[0], *indx);

	*indx = 0;
}

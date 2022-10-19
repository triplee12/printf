#include "main.h"

/**
 * handle_print - prints an argument based on its type
 * @format: formatted string in which to print the arguments
 * @args: list of arguments to be printed
 * @indx: index of characters to be printed
 * @buffer: buffer array to handle print
 * @f: flag specifier
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: 1 on success, otherwise 2
 */

int handle_print(const char *format, int *indx, va_list args, char buffer[], int f, int w, int p, int s)
{
	int i, un_len = 0, printed_ch = -1;
	fmt_t formats[] = {
		{'c', check_char}, {'s', check_string}, {'%', check_modulo},
		{'i', check_int}, {'d', check_int}, {'b', check_binary},
		{'u', check_unsigned}, {'o', check_octal}, {'x', check_hex},
		{'X', check_hex_upper}, {'p', get_memory}, {'S', check_non_printable},
		{'r', print_reverse}, {'R', print_rot13}, {'\0', NULL}
	};
	
	for (i = 0; formats[i].fmt != '\0'; i++)
		if (format[*indx] == formats[i].fmt)
			return (formats[i].func(args, buffer, f, w, p, s));
	if (formats[i].fmt == '\0')
	{
		if (format[*indx] == '\0')
			return (-1);
		un_len += write(1, "%%", 1);

		if (format[*indx - 1] == ' ')
			un_len += write(1, " ", 1);
		else if (w)
		{
			--(*indx);
			while (format[*indx] != ' ' && format[*indx] != '%')
				--(*indx);
			if (format[*indx] == ' ')
				--(*indx);
			return (1);
		}
		un_len += write(1, &format[*indx], 1);
		return (un_len);
	}
	return (printed_ch);
}

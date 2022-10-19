#include "main.h"

/**
 * get_memory - prints values at a specific pointer
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int get_memory(va_list args, char buffer[], int f, int w, int p, int s)
{
	char extra_ch = 0, padd = ' ';
	int indx = BUFFER_S - 2;
	int len = 2;
	int padd_start = 1;
	unsigned long num_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(args, void *);

	UN_USED(w);
	UN_USED(s);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFFER_S - 1] = '\0';
	UN_USED(p);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[indx--] = map_to[num_address % 16];
		num_address /= 16;
		len++;
	}

	if ((f & FLAG_ZERO) && !(f & FLAG_MINUS))
		padd = '0';
	if(f & FLAG_PLUS)
		extra_ch = '+', len++;
	else if (f & FLAG_SPACE)
		extra_ch = ' ', len++;

	indx++;

	return (handle_ptr(buffer, indx, len, w, f, padd, extra_ch, padd_start));
}

/**
 * check_non_printable - checks and prints ascii code non printable characters
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flag
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_non_printable(va_list args, char buffer[], int f, int w, int p, int s)
{
	int i = 0, offset = 0;
	char *str = va_arg(args, char *);

	UN_USED(f);
	UN_USED(w);
	UN_USED(p);
	UN_USED(s);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hex(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * print_reverse - prints reverse string literal
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int print_reverse(va_list args, char buffer[], int f, int w, int p, int s)
{
	char *str;
	int i, counter = 0;

	UN_USED(buffer);
	UN_USED(f);
	UN_USED(w);
	UN_USED(s);

	str = va_arg(args, char *);

	if (str == NULL)
	{
		UN_USED(p);
		
		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		counter++;
	}
	return (counter);
}

/**
 * print_rot13 - prints string in rot13
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int print_rot13(va_list args, char buffer[], int f, int w, int p, int s)
{
	char x, *str;
	unsigned int i, j;
	int counter = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(args, char *);
	UN_USED(buffer);
	UN_USED(f);
	UN_USED(w);
	UN_USED(p);
	UN_USED(s);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				counter++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			counter++;
		}
	}
	return (counter);
}

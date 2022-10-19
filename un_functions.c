#include "main.h"

/**
 * check_unsigned - checks and prints an unsigned number
 * @args: list of arguments
 * @buffer: buffer array
 * @f: checks active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_unsigned(va_list args, char buffer[], int f, int w, int p, int s)
{
	int i = BUFFER_S - 2;
	unsigned long int num = va_arg(args, unsigned long int);

	num = con_size_unsgd(num, s);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_S - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (handle_unsigned(0, i, buffer, f, w, p, s));
}

/**
 * check_octal - checks and prints an unsigned number in octal
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: width specifier
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_octal(va_list args, char buffer[], int f, int w, int p, int s)
{
	int i = BUFFER_S - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_n = num;

	UN_USED(w);

	num = con_size_unsgd(num, s);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_S - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (f & FLAG_HASH && init_n != 0)
		buffer[i--] = '0';

	i++;

	return (handle_unsigned(0, i, buffer, f, w, p, s));
}

/**
 * check_hex - checks and prints an unsigned number in hexadecimal
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_hex(va_list args, char buffer[], int f, int w, int p, int s)
{
	return (check_hexa(args, "0123456789abcdef", buffer, f, 'x', w, p, s));
}

/**
 * check_hex_upper - checks and prints number in uppercase hexadecimal
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_hex_upper(va_list args, char buffer[], int f, int w, int p, int s)
{
	return (check_hexa(args, "0123456789ABCDEF", buffer, f, 'X', w, p, s));
}

/**
 * check_hexa - checks and prints hexadecimal in lowercase or uppercase
 * @args: list of arguments
 * @map_to: array of values to map the number to
 * @buffer: buffer array
 * @f: active flags
 * @f_ch: active flags in character constant
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_hexa(va_list args, char map_to[], char buffer[], int f, char f_ch, int w, int p, int s)
{
	int i = BUFFER_S - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_n = num;

	UN_USED(w);

	num = con_size_unsgd(num, s);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_S - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (f & FLAG_HASH && init_n != 0)
	{
		buffer[i--] = f_ch;
		buffer[i--] = '0';
	}

	i++;

	return (handle_unsigned(0, i, buffer, f, w, p, s));
}

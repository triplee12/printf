#include "main.h"

/**
 * check_char - checks and prints a character constant
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_char(va_list args, char buffer[], int f, int w, int p, int s)
{
	char ch = va_arg(args, int);

	return (handle_char(ch, buffer, f, w, p, s));
}

/**
 * check_string - checks and prints string literal
 * @args: list arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_string(va_list args, char buffer[], int f, int w, int p, int s)
{
	int len = 0, i;
	char *str = va_arg(args, char *);

	UN_USED(buffer);
	UN_USED(f);
	UN_USED(w);
	UN_USED(p);
	UN_USED(s);
	if (str == NULL)
	{
		str = "(null)";
		if (p >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (p >=0 && p < len)
		len = p;

	if (w > len)
	{
		if (f & FLAG_MINUS)
		{
			write(1, &str[0], len);
			for (i = w - len; i > 0; i--)
				write(1, " ", 1);
			return (w);
		}
		else
		{
			for (i = w - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (w);
		}
	}
	
	return (write(1, str, len));
}

/**
 * check_modulo - checks and prints modulo sign
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flag
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_modulo(va_list args, char buffer[], int f, int w, int p, int s)
{
	UN_USED(args);
	UN_USED(buffer);
	UN_USED(f);
	UN_USED(w);
	UN_USED(p);
	UN_USED(s);

	return (write(1, "%%", 1));
}

/**
 * check_int - checks and prints integers
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_int(va_list args, char buffer[], int f, int w, int p, int s)
{
	int i = BUFFER_S - 2;
	int is_negative = 0;
	long int num = va_arg(args, long int);
	unsigned long int Unum;

	num = con_size_num(num, s);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFFER_S - 1] = '\0';
	Unum = (unsigned long int)num;

	if (num < 0)
	{
		Unum = (unsigned long int)((-1) * num);
		is_negative = 1;
	}

	while (Unum > 0)
	{
		buffer[i--] = (Unum % 10) + '0';
		num /= 10;
	}

	i++;

	return (handle_number(is_negative, i, buffer, f, w, p, s));
}

/**
 * check_binary - checks and prints unsigned number
 * @args: list of arguments
 * @buffer: buffer array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int check_binary(va_list args, char buffer[], int f, int w, int p, int s)
{
	unsigned int num, min, i, sum;
	unsigned int a[32];
	int counter;

	UN_USED(buffer);
	UN_USED(f);
	UN_USED(w);
	UN_USED(p);
	UN_USED(s);

	num = va_arg(args, unsigned int);
	min = 2147483648; /* 2^31 */
	a[0] = num / min;
	for (i = 1; i < 32; i++)
	{
		min /= 2;
		a[i] = (num / min) % 2;
	}
	for (i = 0, sum = 0, counter = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 32)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			counter++;
		}
	}

	return (counter);
}

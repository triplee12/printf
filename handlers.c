#include "main.h"

/**
 * handle_char - prints string literal
 * @ch: character types
 * @b: buffer array to print
 * @f: check active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int handle_char(char ch, char buffer[], int f, int w, int p, int s)
{
	int i = 0;
	char padd = ' ';

	UN_USED(p);
	UN_USED(s);

	if (f & FLAG_ZERO)
		padd = '0';

	buffer[i++] = ch;
	buffer[i] = '\0';

	if (w > 1)
	{
		buffer[BUFFER_S - 1] = '\0';
		for (i = 0; i < w - 1; i++)
			buffer[BUFFER_S - i - 2] = padd;

		if (f & FLAG_MINUS)
			return (write(1, &buffer[0], 1) + write(1, &buffer[BUFFER_S - i - 1], w -1));
		else
			return (write(1, &buffer[BUFFER_S - i - 1], w -1) + write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * handle_number - prints a string literal
 * @is_negative: checks list of arguments
 * @indx: char types
 * @buffer: buffer array to print
 * @f: checks active flags
 * @w: get width
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int handle_number(int is_negative, int indx, char buffer[], int f, int w, int p, int s)
{
	int len = BUFFER_S - indx - 1;
	char padd = ' ', extra_ch = 0;

	UN_USED(s);

	if ((f & FLAG_ZERO) && !(f & FLAG_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (f & FLAG_PLUS)
		extra_ch = '+';
	else if (f & FLAG_SPACE)
		extra_ch = ' ';

	return (handle_num(indx, buffer, f, w, p, len, padd, extra_ch));
}

/**
 * handle_num - prints a number using a buffer
 * @indx: index at which the number starts on the buffer
 * @buffer: array
 * @f: active flags
 * @w: get width
 * @p: precision specifier
 * @len: length
 * @padd: padding char
 * @extra_ch: extra character
 *
 * Return: number of printed characters
 */

int handle_num(int indx, char buffer[], int f, int w, int p, int len, char padd, char extra_ch)
{
	int i, padd_start = 1;

	if (p == 0 && indx == BUFFER_S - 2 && buffer[indx] == '0' && w == 0)
		return (0); /* nothing is printed */
	if (p == 0 && indx == BUFFER_S - 2 && buffer[indx] == '0')
		buffer[indx] = padd = ' '; /* padding width with ' ' */
	if (p > 0 && p < len)
		padd = ' ';
	while (p > len)
		buffer[--indx] = '0', len++;
	if (extra_ch != 0)
		len++;
	if (w > len)
	{
		for (i = 1; i < w - len + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (f & FLAG_MINUS && padd == ' ') /* add extra character to left of buffer */
		{
			if (extra_ch)
				buffer[--indx] = extra_ch;
			return (write(1, &buffer[indx], len) + write(1, &buffer[1], i - 1));
		}
		else if (!(f % FLAG_MINUS) && padd == ' ') /* add extra character to left */
		{
			if (extra_ch)
				buffer[--indx] = extra_ch;
			return (write(1, &buffer[1], i -1) + write(1, &buffer[indx], len));
		}
		else if (!(f & FLAG_MINUS) && padd == '0') /* add extra character to left */
		{
			if (extra_ch)
				buffer[--padd_start] = extra_ch;
			return (write(1, &buffer[padd_start], i - padd_start) + write(1, &buffer[indx], len - (1 - padd_start)));
		}
	}
	if (extra_ch)
		buffer[--indx] = extra_ch;

	return (write(1, &buffer[indx], len));
}

/**
 * handle_unsigned - prints an unsigned number
 * @is_negative: number to check if the sum is negative
 * @indx: index at which the number starts in the buffer
 * @buffer: array of characters
 * @f: flag specifier
 * @w: width specifier
 * @p: precision specifier
 * @s: size specifier
 *
 * Return: number of characters printed
 */

int handle_unsigned(int is_negative, int indx, char buffer[], int f, int w, int p, int s)
{
	/* Number stored at the right buffer and starts at the position i */
	int len = BUFFER_S - indx - 1, i = 0;
	char padding = ' ';

	UN_USED(is_negative);
	UN_USED(s);

	if (p == 0 && indx == BUFFER_S - 2 && buffer[indx] == '0')
		return (0); /* no character is printed */

	if (p > 0 && p < len)
		padding = ' ';

	while (p > len)
	{
		buffer[--indx] = '0';
		len++;
	}

	if ((f & FLAG_ZERO) && !(f & FLAG_MINUS))
		padding = '0';

	if (w > len)
	{
		for (i = 0; i < w - len; i++)
			buffer[i] = padding;

		buffer[i] = '\0';

		if (f & FLAG_MINUS) /* asign extra character to left of buffer */
			return (write(1, &buffer[indx], len) + write(1, &buffer[0], i));
		else /* asign extra character to left padding */
			return (write(1, &buffer[0], i) + write(1, &buffer[indx], len));
	}

	return (write(1, &buffer[indx], len));
}

/**
 * handle_ptr - print memory address
 * @buffer: array of characters
 * @indx: index at which the address starts in the memory
 * @len: length of address
 * @w: width specifier
 * @f: flag specifier
 * @padd: character representing the padding specifier
 * @extra_ch: extra character
 * @padd_start: index at which the padding should start
 *
 * Return: number of printed character
 */

int handle_ptr(char buffer[], int indx, int len, int w, int f, char padd, char extra_ch, int padd_start)
{
	int i;

	if (w > len)
	{
		for (i = 3; i < w - len + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (f & FLAG_MINUS && padd == ' ') /* add extra character to left of buffer */
		{
			buffer[--indx] = 'x';
			buffer[--indx] = '0';
			if (extra_ch)
				buffer[--indx] = extra_ch;
			return (write(1, &buffer[indx], len) + write(1, &buffer[3], i - 3));
		}
		else if (!(f & FLAG_MINUS) && padd == ' ') /* add extra character to left of buffer */
		{
			buffer[--indx] = 'x';
			buffer[--indx] = '0';
			if (extra_ch)
				buffer[--indx] = extra_ch;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[indx], len));
		}
		else if (!(f & FLAG_MINUS) && padd == '0') /* add extra character to left of padding */
		{
			if (extra_ch)
				buffer[--padd_start] = extra_ch;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) + write(1, &buffer[indx], len - (1 - padd_start) - 2));
		}
	}
	buffer[--indx] = 'x';
	buffer[--indx] = '0';
	if (extra_ch)
		buffer[--indx] = extra_ch;

	return (write(1, &buffer[indx], BUFFER_S - indx - 1));
}

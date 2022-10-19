#include "main.h"

/**
 * is_printable - checks if a character is printable
 * @ch: character to be checked
 *
 * Return: 1 (true) if yes, otherwise 0 (false)
 */

int is_printable(char ch)
{
	if (ch >= 32 && ch < 127)
		return (1); /* it's printable */

	return (0);
}

/**
 * append_hex - append ascii characters in hexadecimal to buffer
 * @buffer: array of characters
 * @ind: starting index to append
 * @ascii: ascii code
 *
 * Return: always return 3
 */

int append_hex(char ascii, char buffer[], int ind)
{
	char map[] = "0123456789ABCDEF";

	if (ascii < 0)
		ascii *= -1;

	buffer[ind++] = '\\';
	buffer[ind++] = 'x';

	buffer[ind++] = map[ascii / 16];
	buffer[ind] = map[ascii % 16];

	return (3);
}

/**
 * is_digit - checks if a character is a digit
 * @ch: character to check
 *
 * Return: 1 (true) if ch is a digit, otherwise 0 (false)
 */

int is_digit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);

	return (0);
}

/**
 * con_size_num - casts a number to the specific size
 * @num: Number to be casted
 * @s: the type size to be casted
 *
 * Return: casted value
 */

long int con_size_num(long int num, int s)
{
	if (s == LONG_S)
		return (num);
	else if (s == SHORT_S)
		return ((short)num);

	return ((int)num);
}

/**
 * con_size_unsgd - casts a number to the specified size
 * @num: number to be casted
 * @s: number size to be casted
 *
 * Return: casted value
 */

long int con_size_unsgd(unsigned long int num, int s)
{
	if (s == LONG_S)
		return (num);
	else if (s == SHORT_S)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

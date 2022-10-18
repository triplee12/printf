#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define UN_USED(x) (void)(x)
#define BUFFER_S 1024

/* TYPES FLAG */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* SIZES */
#define LONG_S 2
#define SHORT_S 1

/**
 * struct fmt_types - struct type for format type sepcifiers
 * @fmt: the format
 * @func: the function associated to the format
 */

struct fmt_types
{
	char fmt;
	int (*func)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt_types fmt_t - type definition of fmt_types
 * @fmt: the format
 * @fmt_t: the function associated to format
 */
typedef struct fmt_types fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *format, int *i,
va_list args, char buffer[], int f, int w, int p, int s);

/* Check if char constant, string literal and modulo */
int check_char(va_list args, char buffer[], int f, int w, int p, int s);
int check_string(va_list args, char buffer[], int f, int w, int p, int s);
int check_modulo(va_list args, char buffer[], int f, int w, int p, int s);

/* Check for all numerics */
int check_int(va_list args, char buffer[], int f, int w, int p, int s);
int check_binary(va_list args, char buffer[], int f, int w, int p, int s);
int check_unsigned(va_list args, char buffer[], int f, int w, int p, int s);
int check_octal(va_list args, char buffer[], int f, int w, int p, int s);
int check_hex(va_list args, char buffer[], int f, int w, int p, int s);
int check_hex_upper(va_list args, char buffer[], int f, int w, int p, int s);
int check_hexa(va_list args, char map_to[], char buffer[], int f, char f_ch, int w, int p, int s);

/* Check for nonprintable characters */
int check_non_printable(va_list args, char buffer[], int f, int w, int p, int s);

/* Get memory address */
int get_memory(va_list args, char buffer[], int f, int w, int p, int s);

/* Get other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list args);
int get_precision(const char *format, int *i, va_list args);
int get_size(const char *format, int *i);

/* Print string in reverse */
int print_reverse(va_list args, char buffer[], int f, int w, int p, int s);

/* Print a string in rot 13 */
int print_rot13(va_list args, char buffer[], int f, int w, int p, int s);

/* Handle width */
int handle_char(char c, char buffer[], int f, int w, int p, int s);
int handle_number(int is_negative, int indx, char buffer[], int f, int w, int p, int s);
int handle_num(int indx, char buffer[], int f, int w, int p, int s, char padd, char extra_ch);
int handle_ptr(char buffer[], int indx, int s, int w, int f, char padd, char extra_c, int padd_start);
int handle_unsigned(int is_negative, int indx, char buffer[], int f, int w, int p, int s);

/************** Cores ***************/
int is_printable(char var);
int append_hex(char var, char arr[], int num);
int is_digit(char var);
long int con_size_num(long int num, int size);
long int con_size_unsgd(unsigned long int num, int size);

#endif

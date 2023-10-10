#include "shell.h"

/**
 * the_erratoi - converts a string to an integer
 * @c: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int the_erratoi(char *c)
{
	int j = 0;
	unsigned long int result = 0;

	if (*c == '+')
		c++;  /* TODO: why does this make main return 255? */
	for (j = 0;  c[j] != '\0'; j++)
	{
		if (c[j] >= '0' && c[j] <= '9')
		{
			result *= 10;
			result += (c[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * prt_err - prints an error message
 * @data: the parameter & return info struct
 * @str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void prt_err(data_t *data char *str)
{
	the_eputs(data->fname);
	the_eputs(": ");
	print_d(data->line_count, STDERR_FILENO);
	the_eputs(": ");
	the_eputs(info->argv[0]);
	the_eputs(": ");
	the_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @entry: the input
 * @dt: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int entry, int dt)
{
	int (*_the_putchar)(char) = the_putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (dt == STDERR_FILENO)
		_the_putchar = the_eputchar;
	if (entry < 0)
	{
		_abs_ = -entry;
		_the_putchar('-');
		num++;
	}
	else
		_abs_ = entry;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			_the_putchar('0' + current / j);
			num++;
		}
		current %= j;
	}
	_the_putchar('0' + current);
	num++;

	return (num);
}

/**
 * convert_num - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rem_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void rem_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}

#include "blairs_simple_shell.h"


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
	for (j = 0; c[j] != '\0'; j++)
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
 * print_error_message_v2 - prints an error message
 * @data: the parameter & return info struct
 * @str: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error_message_v2(CommandData *data, char *str)
{
	print_error_message(data->program_name);
	print_error_message(": ");
	print_integer_v2(data->line_counter, STDERR_FILENO);
	print_error_message(": ");
	print_error_message(data->argv[0]);
	print_error_message(": ");
	print_error_message(str);
}

/**
 * print_integer_v2 - function prints a decimal (integer) number (base 10)
 * @entry: the input
 * @dt: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_integer_v2(int entry, int dt)
{
	int (*_the_putchar)(char) = print_error_character;
	int j, num = 0;
	unsigned int _abs_, current;

	if (dt == STDERR_FILENO)
		_the_putchar = print_error_character;
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
 * convert_integer_to_string - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_integer_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (base <= 0)
	{

		base = 10;
	}

	if (!(flags & CONVERT_TO_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_TO_LOWERCASE ?
		"0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments_from_string - function replaces
 * first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments_from_string(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}


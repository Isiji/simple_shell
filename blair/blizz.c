#include "shell.h"

/**
 * my_write - custom implementation of write
 * @fd: file descriptor (use STDOUT_FILENO for stdout)
 * @str: string to write
 * @len: number of bytes to write
 * Return: the number of bytes written
 */
ssize_t my_write(int fd, const char *str, size_t len)
{
	ssize_t bytes_written = 0;
	size_t total_written = 0;

	while (total_written < len)
	{
		bytes_written = write(fd, str + total_written, len - total_written);

		if (bytes_written < 0)
			return (total_written);

		total_written += bytes_written;
	}

	return (total_written);
}

/**
 * my_itoa - custom implementation of integer to string conversion
 * @value: integer value
 * @str: character buffer to store the result
 * @base: number base for conversion
 * Return: pointer to the result string
 */
char *my_itoa(int value, char *str)
{
	sprintf(str, "%d", value);
	return (str);
}

/**
 * blizz - custom print function to print to stdout
 * @format: format string
 * @...: variable arguments
 */
void blizz(const char *format, ...)
{
	va_list args;

	char *arg, int_str[20];
	int int_arg;

	va_start(args, format);

	while (*format)
	{
		if (*format != '%')
		{
			my_write(STDOUT_FILENO, format, 1);
		}
		else
		{
			format++;
			switch (*format)
			{
				case 's':
					arg = va_arg(args, char *);
					my_write(STDOUT_FILENO, arg, strlen(arg));
					break;
				case 'd':
					int_arg = va_arg(args, int);
					my_itoa(int_arg, int_str);
					my_write(STDOUT_FILENO, int_str, strlen(int_str));
					break;
			}
		}
		format++;
	}

	va_end(args);
}


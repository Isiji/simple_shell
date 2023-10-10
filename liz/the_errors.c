#include "shell.h"

/**
 * the_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void the_eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		the_eputchar(str[j]);
		j++;
	}
}

/**
 * the_eputchar - writes the character c to stderr
 * @k: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int the_eputchar(char k)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (k != BUF_FLUSH)
		buf[j++] = k;
	return (1);
}

/**
 * the_putdt - writes the character c to given fd
 * @c: The character to print
 * @dt: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int the_putdt(char c, int dt)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(dt, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * the_putsdt - prints an input string
 * @str: the string to be printed
 * @dt: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int the_putsdt(char *str, int dt)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += the_putdt(*str++, dt);
	}
	return (j);
}

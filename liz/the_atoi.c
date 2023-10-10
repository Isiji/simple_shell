#include "shell.h"

/**
 * inter - returns 1 if shell is in interactive mode
 * @data: the struct address
 *
 * Return: 1 if interactive mode, 0 if otherwise
 */
int inter(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readdt <= 2);
}

/**
 * the_delim - checks if character is a delimeter
 * @c: the character to be checked
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int the_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 * the_alph - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int the_alph(int j)
{
	if ((j >= 'a' && j <= 'z') || (j >= 'A' && j <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * the_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int the_atoi(char *s)
{
	int n, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (n = 0; s[n] != '\0' && flag != 2; i++)
	{
		if (s[n] == '-')
			sign *= -1;

		if (s[n] >= '0' && s[n] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

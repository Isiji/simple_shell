#include "shell.h"

/**
 * convert_atoi - converts ASCII to integer
 * @str: pointer to a given integer that is null terminated
 *
 * Return: Sign * end
 */
int convert_atoi(const char *str)
{
	int end = 0;
	int sign = 1;
	int num = 0;

	while (str[num] == ' ' || str[num] == '\t')
		num++;

	if (str[num] == '-')
	{
		sign = -1;
		num++;
	}

	else if (str[num] == '+')
	{
		num++;
	}

	while (str[num] >= '0' && str[num] <= '9')
	{
		end = end * 10 + (str[num] - '0');
		num++;
	}
	return (sign * end);
}


#include "shell.h"

/**
 * the_strchr - shows first occurence of a character in a string
 * @str: pointer to the input for the search
 * @c: character being searched
 * Return: 0
 */
char *the_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}

	return (NULL);
}

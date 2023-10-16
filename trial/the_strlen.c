#include "shell.h"

/**
 * the_strlen - counts the number of characters
 * @str: pointer to the size of length
 * Return: 0
 */
size_t the_strlen(const char *str)
{
	size_t len = 0;

	while (str[len] != '\0')
	{
		len++;
	}

	return (len);
}

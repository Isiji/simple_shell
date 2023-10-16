#include "shell.h"

/**
 * the_strncat - concatenates two strings
 * @dest: pointer to destination
 * @src: pointer to the source string
 * @n: number of characters
 * Return: 0
 */
char *the_strncat(char *dest, const char *src, size_t n)
{
	char *r = dest;

	while (*r != '\0')
	{
		r++;
	}

	while (*src != '\0' && n > 0)
	{
		*r = *src;
		r++;
		src++;
		n--;
	}

	*r = '\0';

	return (dest);
}

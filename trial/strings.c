#include "shell.h"

/**
 * our_strsrc - appends two pointers together
 * @dest: pointer to the destination of string
 * @src: pointer to the source file
 * Return: NULL
 */
char *our_strsrc(char *dest, const char *src)
{
	char *start = dest;

	while (*start != '\0')
	{
		start++;
	}

	while (*src != '\0')
	{
		*start = *src;
		start++;
		src++;
	}

	*start = '\0';

	return (0);
}

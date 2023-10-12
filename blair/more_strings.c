#include "shell.h"

/**
 * the_strdup - creates a duplicate copy of a string
 * @str: pointer to a given string
 *
 * Return: pointer to duplicated string when successful, else return NULL
 */
char *the_strdup(const char *str)
{
	size_t len = strlen(str);
	char *dupl = (char *)malloc(len + 1);

	if (dupl != NULL)
	{
		the_strncpy(dupl, str, len + 1);
	}

	return (dupl);
}

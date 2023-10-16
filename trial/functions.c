#include "shell.h"

/**
 * the_strncpy - used to copy a number of characters
 * @dest: the destination to be copied to
 * @source: where data is copied from
 * @n: number of chars
 * Return: gives destination
 */
char *the_strncpy(char *dest, const char *source, size_t n)
{
	size_t i;

	for (i = 0; i < n && source[i] != '\0'; i++)
	{
		dest[i] = source[i];
	}

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}


#include "shell.h"

/**
 * my_strtok - used to tokenize input
 * @str: the string to be tokenized
 * @delim: delimiter of choce
 * Return: token address
 */
char *my_strtok(char *str, const char *delim)
{
	static char *next;
	char *token;

	if (str != NULL)
	{
		next = str;
	}
	while (*next != '\0' && the_delimiter(*next, delim))
	{
		next++;
	}
	if (*next == '\0')
	{
		return (NULL);
	}
	token = next;

	while (*next != '\0' && !the_delimiter(*next, delim))
	{
		next++;
	}
	if (*next != '\0')
	{
		*next = '\0';
		next++;
	}
	return (token);
}

/**
 * the_delimiter - looks for a delimiter
 * @c: characters to be searched
 * @delim: the delimiter
 * Return: 1 if delimiter is available, 0 otherwise
 */
int the_delimiter(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
		{
			return (1);
		}
		delim++;
	}
	return (0);
}
#include <stdbool.h>
/**
 * the_strcmp - used to compare strings
 * @s1: the first string
 * @s2: the second string
 * Return: always 0 on success
 */
int the_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}
#include "shell.h"
/**
 * tokenizeCommands - breaks down characters to smaller tokens 
 * @message: description
 * @commands: characters
 * @max_commands: maximum number of commands
 */
int tokenizeCommands(char *message, char *commands[], int max_commands)
{
	char *token;
	int num = 0;

	token = my_strtok(message, ";");

	while (token != NULL && num < max_commands)
	{
		commands[num] = the_strdup(token);
		num++;

		token = my_strtok(NULL, ";");
	}

	return (num);
}

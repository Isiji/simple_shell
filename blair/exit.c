#include "blairs_simple_shell.h"


/**
 * copy_string_with_length - Copies a string with a specified maximum length.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @max_length: The maximum number of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *copy_string_with_length(char *destination,
		const char *source, int max_length)
{
int i, j;
max_length = string_length(source);

if (destination == NULL)
{
destination = (char *)malloc(max_length + 1);

}

i = 0;
while (source[i] != '\0' && i < max_length - 1)
{
	destination[i] = source[i];
	i++;
}
if (i < max_length)
{
	j = i;
	while (j < max_length)
	{
		destination[j] = '\0';
		j++;
	}
	destination[i] = '\0';
}
return (destination);
}



/**
 * concatenate_strings_with_length - Concatenates two strings
 * @destination: The first string
 * @source: The second string
 * @max_bytes: The maximum number of bytes to be used
 *
 * Return: The concatenated string
 */
char *concatenate_strings_with_length(char *destination,
		char *source, int max_bytes)
{
	int i, j;
	char *result = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < max_bytes)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < max_bytes)
		destination[i] = '\0';
	return (result);
}

/**
 * find_character_in_string - Locates a character in a string
 * @string: The string to be parsed
 * @character: The character to look for
 *
 * Return: A pointer to the memory area in the string
 */
char *find_character_in_string(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}


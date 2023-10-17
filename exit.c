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
	int z = 0;

	while (source[z] != '\0' && z < max_length - 1)
	{
		destination[z] = source[z];
		z++;
	}
	destination[z] = '\0';
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
	int t, p;
	char *result = destination;

	t = 0;
	p = 0;
	while (destination[t] != '\0')
		t++;
	while (source[p] != '\0' && p < max_bytes)
	{
		destination[t] = source[p];
		t++;
		p++;
	}
	if (p < max_bytes)
		destination[t] = '\0';
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

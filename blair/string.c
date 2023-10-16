#include "blairs_simple_shell.h"

/**
 * string_length - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int string_length(const char *str)
{
	int len = 0;

	if (!str)
		return (0);

	while (*str++)
	{
		len++;
	}

	return (len);
}

/**
 * compare_strings - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2,
 * zero if str1 == str2
 */
int compare_strings(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * string_starts_with - checks if needle starts with haystack
 * @search: string to search
 * @substring: the substring to find
 *
 * Return: address of the next character of haystack or NULL
 */
char *string_starts_with(const char *search, const char *substring)
{
	while (*substring)
	{
		if (*substring++ != *search++)
		{
			return (NULL);
		}
	}

	return ((char *)search);
}

/**
 * concatenate_strings - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *concatenate_strings(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
	{
		destination++;
	}

	while (*source)
	{
		*destination++ = *source++;
	}

	*destination = *source;

	return (result);
}


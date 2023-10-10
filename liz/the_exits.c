#include "shell.h"

/**
 **the_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@t: the amount of characters to be copied
 *Return: the concatenated string
 */
char *the_strncpy(char *dest, char *src, int t)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < t - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < t)
	{
		j = i;
		while (j < t)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **the_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@t: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *the_strncat(char *dest, char *src, int t)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < t)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < t)
		dest[i] = '\0';
	return (s);
}

/**
 **the_strchr - locates a character in a string
 *@str: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *the_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

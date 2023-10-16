#include "shell.h"

/**
 * the_strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int the_strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * the_strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int the_strcmp(char *str1, char *str2)
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
 * our_node - checks if needle starts with haystack
 * @srch: string to search
 * @sub_srch: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *our_node(const char *srch, const char *sub_srch)
{
	while (*sub_srch)
		if (*sub_srch++ != *srch++)
			return (NULL);
	return ((char *)srch);
}

/**
 * the_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *the_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

#include "blairs_simple_shell.h"

/**
 * list_length - determines the length of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_length(const StringList *h)
{
	size_t size = 0;

	while (h)
	{
		h = h->next;
		size++;
	}

	return (size);
}

/**
 * get_list_strings - returns an array of strings from the list->str
 * @h: pointer to the first node
 *
 * Return: array of strings
 */
char **get_list_strings(StringList *h)
{
	StringList *node = h;
	size_t size = list_length(h);
	size_t i, j;
	char **strings;
	char *str;

	if (!h || !size)
		return (NULL);

	strings = malloc(sizeof(char *) * (size + 1));
	if (!strings)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = duplicate_string(node->str);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		strings[i] = str;
	}

	strings[i] = NULL;
	return (strings);
}

/**
 * print_linked_list - prints all elements of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_linked_list(const StringList *h)
{
	size_t size = 0;

	while (h)
	{
		print_string(convert_integer_to_string(h->number, 10, 0));
		print_character(':');
		print_character(' ');
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		size++;
	}

	return (size);
}

/**
 * find_prefixed_node - returns a node whose string starts with a prefix
 * @node: pointer to the list head
 * @prefix: string to match as a prefix
 * @needle: the character after the prefix to match
 *
 * Return: matching node or NULL
 */
StringList *find_prefixed_node(StringList *node, char *prefix, char needle)
{
	const char *ptr = NULL;

	while (node)
	{
		ptr = string_starts_with(node->str, prefix);
		if (ptr && ((needle == -1) || (*ptr == needle)))
			return (node);
		node = node->next;
	}

	return (NULL);
}

/**
 * find_node_index - gets the index of a node in the list
 * @h: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t find_node_index(StringList *h, StringList *node)
{
	size_t index = 0;

	while (h)
	{
		if (h == node)
			return (index);
		h = h->next;
		index++;
	}

	return (-1);
}


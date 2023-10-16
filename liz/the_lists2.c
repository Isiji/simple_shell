#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_str - returns an array of strings of the list->str
 * @h: pointer to first node
 *
 * Return: array of strings
 */
char **list_str(list_t *h)
{
	list_t *node = h;
	size_t i = list_len(h), j;
	char **strs;
	char *str;

	if (!h || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(the_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = the_strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		the_puts(convert_num(h->num, 10, 0));
		the_putchar(':');
		the_putchar(' ');
		the_puts(h->str ? h->str : "(nil)");
		the_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @pref: string to match
 * @n: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *starts_with(list_t *node, char *pre char n)
{
	char *k = NULL;

	while (node)
	{
		k = our_node(node->str, pref);
		if (k && ((n == -1) || (*k == n)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - gets the index of a node
 * @h: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t node_index(list_t *h, list_t *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}

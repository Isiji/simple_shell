#include "shell.h"

/**
 * the_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int the_history(data_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(data_t *data, char *str)
{
	char *p, c;
	int rn;

	p = the_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	rn = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, node_starts_with(data->alias, str, -1)));
	*p = c;
	return (rn);
}

/**
 * set_alias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(data_t *data, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(data, str));

	unset_alias(data, str);
	return (add_node_end(&(data->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		the_putchar(*a);
		the_putchar('\'');
		the_puts(p + 1);
		the_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * the_alias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
iint the_alias(data_t *data)
{
	int j = 0;
	char *t = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; data->argv[j]; j++)
	{
		t = the_strchr(data->argv[j], '=');
		if (t)
			set_alias(data, data->argv[j]);
		else
			print_alias(node_starts_with(data->alias, data->argv[j], '='));
	}

	return (0);
}

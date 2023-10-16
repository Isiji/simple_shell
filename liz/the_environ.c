#include "shell.h"

/**
 * the_env - prints the current environment
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int the_env(data_t *data)
{
	print_list(data->env);
	return (0);
}

/**
 * the_getenv - gets the value of an environ variable
 * @data: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *the_getenv(data_t *data, const char *name)
{
	list_t *node = data->env;
	char *t;

	while (node)
	{
		t = node_start(node->str, name);
		if (t && *t)
			return (t);
		node = node->next;
	}
	return (NULL);
}

/**
 * the_setenvr - Initialize a new environment variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int the_setenvr(data_t *data)
{
	if (data->argc != 3)
	{
		the_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (the_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * the_unsetenvr - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int the_unsetenvr(data_t *data)
{
	int j;

	if (data->argc == 1)
	{
		the_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= data->argc; j++)
		the_unsetenv(data, data->argv[j]);

	return (0);
}

/**
 * pop_envlist - populates env linked list
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int pop_envlist(data_t *data)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		the_node_end(&node, environ[j], 0);
	data->env = node;
	return (0);
}

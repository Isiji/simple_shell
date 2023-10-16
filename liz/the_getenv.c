#include "shell.h"

/**
 * get_env - returns the string array copy of our environ
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_env(data_t *data)
{
	if (!data->env || data->env_changed)
	{
		data->env = list_to_strings(data->env);
		data->env_changed = 0;
	}

	return (data->env);
}

/**
 * the_unsetenv - Remove an environment variable
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int the_unsetenv(data_t *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = node_start(node->str, var);
		if (p && *p == '=')
		{
			data->env_changed = delete_node(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}

/**
 * the_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int the_setenv(data_t *data, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(the_strlen(var) + the_strlen(value) + 2);
	if (!buf)
		return (1);
	the_strcpy(buf, var);
	the_strcat(buf, "=");
	the_strcat(buf, value);
	node = data->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	the_node_end(&(data->env), buf, 0);
	free(buf);
	data->env_changed = 1;
	return (0);
}

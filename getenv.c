#include "blairs_simple_shell.h"

/**
 * get_custom_environment - Returns the string array copy of our environment
 * @data: Structure containing potential arguments.
 *
 * Return: A copy of the environment strings
 */
char **get_custom_environment(CommandData *data)
{

	if (!data->env || data->environment_changed)
	{
		data->environ = get_list_strings(data->env);
		data->environment_changed = 0;
	}
	return (data->environ);
}

/**
 * unset_custom_environment_variable - Remove an environment variable
 * @data: Structure containing potential arguments.
 * @variable: The name of the environment variable to unset
 *
 * Return: 1 on success, 0 otherwise
 */
int unset_custom_environment_variable(CommandData *data, char *variable)
{
	StringList *node = data->env;
	size_t index = 0;
	char *prefix;

	if (!node || !variable)
		return (0);

	while (node)
	{
		prefix = string_starts_with(node->str, variable);
		if (prefix && *prefix == '=')
		{
			data->environment_changed = delete_list_node(&(data->env), index);
			index = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (data->environment_changed);
}

/**
 * set_custom_environment_variable - Initialize a new
 * environment variable, or modify an existing one
 * @data: Structure containing potential arguments.
 * @variable: The name of the environment variable to set
 * @value: The value to assign to the environment variable
 *
 * Return: 0 on success, 1 on error
 */
int set_custom_environment_variable(CommandData *data,
		char *variable, char *value)
{
	StringList *node;
	char *prefix;
	char *buffer = NULL;

	if (!variable || !value)
		return (0);

	buffer = malloc(string_length(variable) + string_length(value) + 2);
	if (!buffer)
		return (1);

	copy_string(buffer, variable);
	concatenate_strings(buffer, "=");
	concatenate_strings(buffer, value);

	node = data->env;
	while (node)
	{
		prefix = string_starts_with(node->str, variable);
		if (prefix && *prefix == '=')
		{
			free(node->str);
			node->str = buffer;
			data->environment_changed = 1;
			return (0);
		}
		node = node->next;
	}

	create_list_node_at_end(&(data->env), buffer, 0);
	free(buffer);
	data->environment_changed = 1;
	return (0);
}


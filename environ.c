#include "blairs_simple_shell.h"

/**
 * handle_environment - Prints the current environment
 * @data: Pointer to the CommandData struct
 *
 * Return: Always 0
 */
int handle_environment(CommandData *data)
{
	print_list_strings(data->env);
	return (0);
}

/**
 * get_environment_variable - Gets the value of an environment variable
 * @data: Pointer to the CommandData struct
 * @variable_name: The environment variable name
 *
 * Return: The value of the environment variable
 */
char *get_environment_variable(CommandData *data, const char *variable_name)
{
	StringList *node = data->env;
	char *a;

	while (node)
	{
		a = string_starts_with(node->str, variable_name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_environment_variable - Initializes a new environment
 * variable or modifies an existing one
 * @data: Pointer to the CommandData struct
 *
 * Return: Always 0
 */
int set_environment_variable(CommandData *data)
{
	if (data->argument_count != 3)
	{
		print_error_message("Incorrect number of arguments\n");
		return (1);
	}
	if (set_custom_environment_variable(data,
				data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_environment_variable - Removes an environment variable
 * @data: Pointer to the CommandData struct
 *
 * Return: Always 0
 */
int unset_environment_variable(CommandData *data)
{
	int z;

	if (data->argument_count == 1)
	{
		print_error_message("Too few arguments.\n");
		return (1);
	}
	for (z = 1; z <= data->argument_count; z++)
		unset_custom_environment_variable(data, data->argv[z]);

	return (0);
}

/**
 * pop_environment_list - Populates the environment linked list
 * @data: Pointer to the CommandData struct
 *
 * Return: Always 0
 */
int pop_environment_list(CommandData *data)
{
	StringList *node = NULL;
	size_t p;

	for (p = 0; environ[p]; p++)
		create_list_node_at_end(&node, environ[p], 0);
	data->env = node;
	return (0);
}

#include "blairs_simple_shell.h"

/**
 * execute_history - Displays the history list, one command per line,
 * preceded with line numbers, starting at 0.
 * @data: Pointer to the CommandData struct
 *
 * Return: Always 0
 */
int execute_history(CommandData *data)
{
	print_list_strings(data->history);
	return (0);
}

/**
 * remove_alias - Removes an alias from the list
 * @data: Pointer to the CommandData struct
 * @alias_string: The alias string to remove
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(CommandData *data, char *alias_string)
{
	char *alias_name, alias_character;
	int removal_result;

	alias_name = find_character_in_string(alias_string, '=');
	if (!alias_name)
		return (1);
	alias_character = *alias_name;
	*alias_name = 0;
	removal_result = delete_list_node(&(data->alias), find_node_index(data->alias,
				find_prefixed_node(data->alias, alias_string, -1)));
	*alias_name = alias_character;
	return (removal_result);
}

/**
 * create_alias - Sets an alias to a string
 * @data: Pointer to the CommandData struct
 * @alias_string: The alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int create_alias(CommandData *data, char *alias_string)
{
	char *alias_value;

	alias_value = find_character_in_string(alias_string, '=');
	if (!alias_value)
		return (1);
	if (!*++alias_value)
		return (remove_alias(data, alias_string));

	remove_alias(data, alias_string);
	return (create_list_node_at_end(&(data->alias), alias_string, 0) == NULL);
}

/**
 * print_alias - Prints an alias string
 * @node: The alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(StringList *node)
{
	char *pointer = NULL, *alias = NULL;

	if (node)
	{
		pointer = find_character_in_string(node->str, '=');
		for (alias = node->str; alias <= pointer; alias++)
			print_character(*alias);
		print_character('\'');
		print_string(pointer + 1);
		print_string_descriptor("\n", STDOUT_FILENO);
		return (0);
	}
	return (1);
}

/**
 * execute_alias - Mimics the alias builtin (man alias)
 * @data: Pointer to the CommandData struct
 *
 * Return: Always 0
 */
int execute_alias(CommandData *data)
{
	int j = 0;
	char *t = NULL;
	StringList *node = NULL;

	if (data->argument_count == 1)
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
		t = find_character_in_string(data->argv[j], '=');
		if (t)
			create_alias(data, data->argv[j]);
		else
			print_alias(find_prefixed_node(data->alias, data->argv[j], '='));
	}

	return (0);
}


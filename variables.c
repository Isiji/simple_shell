#include "blairs_simple_shell.h"

/**
 * is_command_chain - checks if the current character
 * in the buffer is a chain delimiter
 * @data: the parameter struct
 * @buf: the character buffer
 * @current_position: address of the current position in buf
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int is_command_chain(CommandData *data, char *buf,
						  size_t *current_position)
{
	size_t j = *current_position;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data->command_buffer_type = OR_COMMAND;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->command_buffer_type = AND_COMMAND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		data->command_buffer_type = CHAIN_COMMAND;
	}
	else
	{
		return (0);
	}

	*current_position = j;
	return (1);
}

/**
 * check_command_chain - checks if we should continue
 * chaining based on the last status
 * @data: the parameter struct
 * @buf: the character buffer
 * @current_position: address of the current position in buf
 * @start_position: starting position in buf
 * @buffer_length: length of buf
 *
 * Return: Void
 */
void check_command_chain(CommandData *data, char *buf, size_t
							 *current_position, size_t start_position, size_t buffer_length)
{
	size_t j = *current_position;

	if (data->command_buffer_type == AND_COMMAND)
	{
		if (data->status)
		{
			buf[start_position] = 0;
			j = buffer_length;
		}
	}
	if (data->command_buffer_type == OR_COMMAND)
	{
		if (!data->status)
		{
			buf[start_position] = 0;
			j = buffer_length;
		}
	}

	*current_position = j;
}

/**
 * replace_command_alias - replaces an alias in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_command_alias(CommandData *data)
{
	int i;
	StringList *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = find_prefixed_node(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);

		p = find_character_in_string(node->str, '=');

		if (!p)
			return (0);

		p = duplicate_string(p + 1);

		if (!p)
			return (0);

		data->argv[0] = p;
	}
	return (1);
}


/**
 * replace_command_variables - replaces variables in the tokenized command
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_command_variables(CommandData *data)
{
	int i = 0;
	StringList *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;

		if (!compare_strings(data->argv[i], "$?"))
		{
			replace_string(&(data->argv[i]),
						   duplicate_string(convert_integer_to_string(data->status, 10, 0)));
			continue;
		}

		if (!compare_strings(data->argv[i], "$$"))
		{
			replace_string(&(data->argv[i]),
						   duplicate_string(convert_integer_to_string(getpid(), 10, 0)));
			continue;
		}

		node = find_prefixed_node(data->env, &data->argv[i][1], '=');
		if (node)
		{
			replace_string(&(data->argv[i]),
						   duplicate_string(find_character_in_string(node->str, '=') + 1));
			continue;
		}

		replace_string(&data->argv[i], duplicate_string(""));
	}

	return (0);
}



/**
 * replace_string - replaces a string
 * @previous: address of the old string
 * @new_string: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **previous, char *new_string)
{
	free(*previous);
	*previous = new_string;
	return (1);
}


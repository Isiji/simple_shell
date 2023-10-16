#include "blairs_simple_shell.h"

/**
 * clear_command_data - Initializes the CommandData struct fields
 * @data: struct address to be initialized
 */
void clear_command_data(CommandData *data)
{
	data->arguments = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argument_count = 0;
}

/**
 * set_command_data - Initializes the CommandData struct
 * fields from the argument vector
 * @data: struct address to be initialized
 * @av: argument vector
 */
void set_command_data(CommandData *data, char **av)
{
	int i = 0;

	data->program_name = av[0];
	if (data->arguments)
	{
		data->argv = split_string(data->arguments, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = duplicate_string(data->arguments);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argument_count = i;

		replace_command_alias(data);
		replace_command_variables(data);
	}
}

/**
 * free_command_data - Frees the CommandData struct fields
 * @data: struct address to be freed
 * @free_all: true if freeing all fields
 */
void free_command_data(CommandData *data, int free_all)
{
	free_string_array(data->argv);
	data->argv = NULL;
	data->path = NULL;

	if (free_all)
	{
		if (!data->command_buffer)
			free(data->arguments);
		if (data->env)
			free_list_node(&data->env);
		if (data->history)
			free_list_node(&(data->history));
		if (data->alias)
			free_list_node(&(data->alias));
		free_string_array(data->environ);
		data->environ = NULL;
		free_pointer((void **)data->command_buffer);
		if (data->read_descriptor > 2)
			close(data->read_descriptor);
		print_character(BUFFER_FLUSH);
	}
}


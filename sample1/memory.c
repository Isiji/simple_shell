#include "blairs_simple_shell.h"

/**
 * free_pointer - frees a pointer and sets it to NULL
 * @pointer: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_pointer(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

/**
 * startsWith - checks if a string starts with a specific prefix
 * @str: string to be checked
 * @prefix: the prefix to check for
 * Return: true if succesful
 */
bool startsWith(const char *str, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix != *str)
		{
			return (false);
		}
		prefix++;
		str++;
	}
	return (true);
}

/**
 * free_environment - frees the linked list of environment variables
 * @head: Pointer to the head of the linked list
 */
void free_environment(StringList *head)
{
	StringList *node = head;

	while (node)
	{
		StringList *next = node->next;

		free(node->str);
		free(node);
		node = next;
	}
}

/**
 * initialize_command_data - Initializes the CommandData struct fields
 * @data: struct address to be initialized
 */
void initialize_command_data(CommandData *data)
{
	data->arguments = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argument_count = 0;
	data->line_counter = 0;
	data->error_number = 0;
	data->linecount_flag = 0;
	data->program_name = NULL;
	data->env = NULL;
	data->history = NULL;
	data->alias = NULL;
	data->environ = NULL;
	data->environment_changed = 0;
	data->status = 0;
	data->command_buffer = NULL;
	data->command_buffer_type = 0;
	data->read_descriptor = 0;
	data->history_count = 0;
}


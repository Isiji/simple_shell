#include "blairs_simple_shell.h"



/**
 * get_history_file - gets the history file path
 * @data: parameter struct
 *
 * Return: Allocated string containing history file path
 */
char *get_history_file(CommandData *data)
{
	char *buf, *dir;

	dir = get_environment_variable(data, "HOME");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (string_length(dir) +
				string_length(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	copy_string(buf, dir);
	concatenate_strings(buf, "/");
	concatenate_strings(buf, HISTORY_FILE);

	return (buf);
}

/**
 * write_command_history - saves command history to a file
 * @data: parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int write_command_history(CommandData *data)
{
	ssize_t file_desc;
	char *filename = get_history_file(data);
	StringList *node = data->history;

	if (!filename)
		return (-1);

	file_desc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (file_desc == -1)
		return (-1);

	while (node)
	{
		print_string_descriptor(node->str, file_desc);
		print_string_descriptor("\n", file_desc);
		node = node->next;
	}

	fflush(stdout);

	close(file_desc);

	return (1);
}

/**
 * read_command_history - loads command history from a file
 * @data: parameter struct
 *
 * Return: histcount on success, 0 on failure
 */
int read_command_history(CommandData *data)
{
	int i, last = 0, linecount = 0;
	ssize_t file_desc, read_len, file_size = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(data);

if (!filename)
	return (0);
file_desc = open(filename, O_RDONLY);
free(filename);
if (file_desc == -1)
	return (0);
if (!fstat(file_desc, &st))
	file_size = st.st_size;
if (file_size < 2)
	return (0);
buffer = malloc(sizeof(char) * (file_size + 1));
if (!buffer)
	return (0);
read_len = read(file_desc, buffer, file_size);
buffer[file_size] = 0;
if (read_len <= 0)
	return (free(buffer), 0);
close(file_desc);
for (i = 0; i < file_size; i++)
{
	if (buffer[i] == '\n')
	{
		buffer[i] = 0;
		build_command_history(data, buffer + last, linecount++);
		last = i + 1;
	}
}
if (last != i)
	build_command_history(data, buffer + last, linecount++);
free(buffer);
data->history_count = linecount;
while (data->history_count-- >= MAX_HISTORY_ENTRIES)
	delete_list_node(&(data->history), 0);
renumber_command_history(data);
return (data->history_count);
}

/**
 * build_command_history - adds an entry to the history linked list
 * @data: parameter struct
 * @buf: buffer
 * @linecount: the history line count (history_count)
 *
 * Return: Always 0
 */
int build_command_history(CommandData *data, char *buf, int linecount)
{
	StringList *node = NULL;

	if (data->history)
		node = data->history;

	create_list_node_at_end(&node, buf, linecount);

	if (!data->history)
		data->history = node;

	return (0);
}

/**
 * renumber_command_history - renumbers the history linked list after changes
 * @data: parameter struct
 *
 * Return: the new history_count
 */
int renumber_command_history(CommandData *data)
{
	StringList *node = data->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}

	return (data->history_count = i);
}


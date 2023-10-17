#include "blairs_simple_shell.h"


/**
 * handle_command - determines if a file is an executable command
 * @data: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */

int handle_command(CommandData *data, char *path)
{
	struct stat s;

(void)data;
if (!path || stat(path, &s))
	return (0);

if (s.st_mode & S_IFREG)
{
	return (1);
}
return (0);
}

/**
 * dup_chars - duplicates characters
 * @path_s: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_s, int start, int stop)
{
	static char buf[1024];
	int j = 0, size = 0;

	for (j = 0, size = start; size < stop; size++)
		if (path_s[size] != ':')
			buf[j++] = path_s[size];
	buf[j] = 0;
	return (buf);
}

/**
 * find_command_path - finds this cmd in the PATH string
 * @data: the info struct
 * @path_s: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_command_path(CommandData *data, char *path_s, char *cmd)
{
	int size = 0, curr_pos = 0;
	char *path;

	if (!path_s)
		return (NULL);
	if ((string_length(cmd) > 2) && startsWith(cmd, "./"))
	{
		if (handle_command(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_s[size] || path_s[size] == ':')
		{
			path = dup_chars(path_s, curr_pos, size);
			if (!*path)
				concatenate_strings(path, cmd);
			else
			{
				concatenate_strings(path, "/");
				concatenate_strings(path, cmd);
			}
			if (handle_command(data, path))

				return (path);
			if (!path_s[size])
				break;
			curr_pos = size;
		}
		size++;
	}
	return (NULL);
}


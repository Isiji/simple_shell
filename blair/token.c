#include "shell.h"
/**
 * tokenization - reads a command line
 * @max_arguments: the maximum number of arguments
 * @str: this is the line of command
 * @args: arguments entered
 * Return: always 0 on succes
 */

int tokenization(char *str, char *args[], int max_arguments)
{
	char *token;
	int argc = 0;
	const char *delimiter = " \t\n";

	token = my_strtok(str, delimiter);

	while (token != NULL && argc < max_arguments - 1)
	{
		token = trim_whitespace(token);

		if (*token != '\0')
		{
		args[argc] = the_strdup(token);
		argc++;
		}

		token = my_strtok(NULL, delimiter);
	}
	args[argc] = NULL;

	return (argc);

}

#include "shell.h"
/**
 * search_command - looks for a command in the PATH
 * @command: the command to be found
 * @pathenv: the PATH environment
 * @bufpath: the buffer to store the full path
 * @bufpath_len: maximum length of the path buffer
 * Return: 1 if path is found, otherwise 0
 */
int search_command(const char *command, const char *pathenv,
		char *bufpath, size_t bufpath_len)
{
	const char *ptr = pathenv;
	size_t seglen, command_len = the_strlen(command);

	while (ptr != NULL)
	{
		const char *end = strchr(ptr, ':');

		if (end == NULL)
		{
			end = ptr + the_strlen(ptr);
		}
		seglen = end - ptr;

		if (seglen + command_len + 2 <= bufpath_len)
		{
			the_strncpy(bufpath, ptr, seglen);
			bufpath[seglen] = '/';
			the_strncpy(bufpath + seglen + 1, command, bufpath_len - seglen - 1);

			if (access(bufpath, X_OK) == 0)
			{
				return (1);
			}
		}
		if (*end == ':')
		{
			ptr = end + 1;
		}
		else
		{
			break;
		}
	}
	return (0);
}

#include "shell.h"

/**
 * trim_whitespace - Removes leading and trailing whitespace from a string.
 * @str: The input string to trim.
 * Return: A pointer to the trimmed string.
 */
char *trim_whitespace(char *str)
{
	char *end;

	while (the_isspace(*str))
	{
		str++;
	}

	if (*str == '\0')
	{
		return (str);
	}

	end = str + the_strlen(str) - 1;

	while (end > str && the_isspace(*end))
	{
		end--;
	}

	*(end + 1) = '\0';

	return (str);
}


/**
 * the_isspace - Checks if a character is a whitespace
 * character (space or tab).
 * @c: The character to check.
 * Return: 1 if the character is a whitespace character, otherwise 0.
 */
int the_isspace(char c)
{
	return (c == ' ' || c == '\t');
}


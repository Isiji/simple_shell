#include "shell.h"

/**
 * get_command - reads the command from the std input
 * @command: pointer to message to be processed
 * @size: number of entries
 * Return: a pointer to the input command
 */
void *get_command(char *command, size_t size)
{
	size_t len;

	if (fgets(command, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			blizz("\n");
			exit(EXIT_SUCCESS);
		}

		else
		{
			blizz("didn't get input\n");
			exit(EXIT_FAILURE);
		}
	}
	len = strlen(command);

	if (len > 0 && command[len - 1] == '\n')
	{command[len - 1] = '\0';
	}
	return (command);
}

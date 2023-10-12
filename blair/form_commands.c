#include "shell.h"

/**
 * changeDirectory - command that changes the working directory
 * @path: shows the address of file or directory
 *
 */
void changeDirectory(const char *path)
{
	if (path)
	{
		char *current_dir = getcwd(NULL, 0);

		if (current_dir)
		{
			setenv("OLDPWD", current_dir, 1);
			free(current_dir);
		}
		if (chdir(path) == 0)
		{
			setenv("PWD", path, 1);
		}
		else
		{
			perror("cd");
		}
	}
	else
	{
		blizz("$HOME is not defined\n");
	}
}

#include "shell.h"

/**
 * handleSetenvCommand - sets the environment variables
 * @args: pointer to the argument
 * @argc: counts the number of arguments
 *
 */
void handleSetenvCommand(char *args[], int argc)
{

	if (argc != 3)
	{
		blizz("Usage: setenv VARIABLE VALUE\n");
		return;
	}

		if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
	}
}

#include "shell.h"

/**
 * handleUnsetenvCommand - unsets environment variables
 * @args: pointer to the first argument
 * @argc: holds count of the arguments
 *
 */
void handleUnsetenvCommand(char *args[], int argc)
{

	if (argc != 2)
	{
		blizz("Usage: unsetenv VARIABLE\n");
		return;
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
	}
}

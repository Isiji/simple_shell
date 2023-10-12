#include "shell.h"
/**
 * execution - used to execute other procesess
 * @message: the command to be executed
 * @pathenv: pointer to the path
 */


void execution(char *message, const char *pathenv)
{
	char *commands[MAX_INPUT_SIZE], pid_str[10];
	int num = tokenizeCommands(message, commands, MAX_INPUT_SIZE);
	int i, prev, pid_length;
	char replacedCommand[MAX_INPUT_SIZE];

	for (i = 0; i < num; i++)
	{
	char *args[MAX_INPUT_SIZE];
	char *envp[] = { NULL };
	int argc, j;
	pid_t baby_pid = -1;
	char bufpath[BUFPATH_LEN];

	argc = tokenization(message, args, MAX_INPUT_SIZE);

	if (argc == 0)
	{
		blizz("No command entered\n");
		continue;
	}
	for (j = 0; j < argc; j++)
	{
		if (the_strcmp(args[j], "#") == 0)
			break;
	}
	if (j < argc)
	{
		argc = j;
	}


	replaceExitStatus(args, argc, prev);

	replaceProcessID(args, argc);

	reconstructCommand(replacedCommand, args, argc);

	if (the_strcmp(args[0], "exit") == 0)
	{
		handleExitCommand(args, argc);
		return;
	}
	else if (the_strcmp(args[0], "cd") == 0)
	{
		handleCdCommand(args, argc);
	}
	else if (the_strcmp(args[0], "setenv") == 0)
	{
		handleSetenvCommand(args, argc);
	}
	else if (the_strcmp(args[0], "unsetenv") == 0)
	{
		handleUnsetenvCommand(args, argc);
	}
	else if (the_strcmp(args[0], "&&") == 0)
	{
		if (prev == 0)
		{
			executeExternalCommand(args + 1, argc - 1,
					envp, bufpath, baby_pid, pathenv);
			wait(NULL);
			prev = (baby_pid == -1) ? 1 : WEXITSTATUS(baby_pid);
		}
	}
	else if (the_strcmp(args[0], "||") == 0)
	{
		if (prev != 0)
		{
			executeExternalCommand(args + 1, argc - 1, envp,
					bufpath, baby_pid, pathenv);
			wait(NULL);
			prev = (baby_pid == -1) ? 1 : WEXITSTATUS(baby_pid);

		}
	}
	else
	{
		if (the_strcmp(args[0], "echo") == 0 && the_strcmp(args[1], "$$") == 0)
		{
			pid_length = our_itoa(getpid(), pid_str);

			write(STDOUT_FILENO, pid_str, pid_length);
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		{
		executeExternalCommand(args, argc, envp, bufpath, baby_pid, pathenv);
		wait(NULL);
		prev = (baby_pid == -1) ? 1 : WEXITSTATUS(baby_pid);
		}
	}
	}
}

#include "shell.h"
/**
 * handleExitCommand - handles exit command
 * @args: numner of arguments
 * @argc: number of counts
 */
void handleExitCommand(char *args[], int argc)
{
	if (argc == 1)
	{
		my_exit(EXIT_SUCCESS);
	}
	else if (argc == 2)
	{
		int exit_status = convert_atoi(args[1]);

		my_exit(exit_status);
	}
	else
	{
		blizz("Too many arguments for exit\n");
	}
}

#include "shell.h"
/**
 * handleCdCommand - deals with the change directory command
 * @args: number of arguments
 * @argc: number of counts
 */

void handleCdCommand(char *args[], int argc)
{
	if (argc == 1)
	{
		changeDirectory(getenv("HOME"));
	}
	else if (argc == 2)
	{
		if (the_strcmp(args[1], "-") == 0)
		{
			changeDirectory(getenv("OLDPWD"));
		}
		else
		{
			changeDirectory(args[1]);
		}
	}
	else
	{
		blizz("Too many arguments for cd\n");
	}
}
#include "shell.h"

/**
 * executeExternalCommand - executes external commands
 * @args: first argument
 * @argc: number of counts of arguments
 * @envp: pointer to the environment
 * @bufpath: path
 * @pathenv: pointer to the path's environment
 * @baby_pid: process ID of child
 */

void executeExternalCommand(char* args[], int argc, char* envp[],
				char* bufpath, pid_t baby_pid, const char* pathenv)
{
	char debug_message[100];
	int debug_length = snprintf(debug_message, sizeof(debug_message),
			"Executing command: %s\n", args[0]);
	write(STDERR_FILENO, debug_message, debug_length);

	baby_pid = fork();

	if (baby_pid == -1)
	{
		perror("unable to fork");
		exit(EXIT_FAILURE);
	}
	else if (baby_pid == 0)
	{
		args[argc] = NULL;

		if (access(args[0], X_OK) == 0)
		{
			execve(args[0], args, envp);
			perror("execve failure");
			exit(EXIT_FAILURE);
		}

		if (!search_command(args[0], pathenv, bufpath, BUFPATH_LEN))
		{
			debug_length = snprintf(debug_message, sizeof(debug_message),
					"%s: command not found\n", args[0]);
			write(STDERR_FILENO, debug_message, debug_length);

			write(STDERR_FILENO, args[0], the_strlen(args[0]));
			blizz(": command not found\n");
			exit(EXIT_FAILURE);
		}

		if (execve(bufpath, args, envp) == -1)
		{
			perror("execve failure");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}

	debug_length = snprintf(debug_message, sizeof(debug_message),
			"Command execution finished: %s\n", args[0]);
	write(STDERR_FILENO, debug_message, debug_length);
}


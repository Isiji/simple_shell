#include "blairs_simple_shell.h"

/**
 * shell_loop - Main shell loop
 * @arguments: Argument vector from main()
 * @data: information entered
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(CommandData *data, char **arguments)
{
	int builtin_return = 0;
	ssize_t n = 0;

	while (n != -1 && builtin_return != -2)
	{
		clear_command_data(data);

		if (interpret(data))
			print_string("HOME $ ");
		print_error_character(BUFFER_FLUSH);
		n = read_input(data);

		if (n != -1)
		{
			set_command_data(data, arguments);
			builtin_return = find_builtin(data);
			if (builtin_return == -1)
				find_command(data);
		}
		else if (interpret(data))
			print_character('\n');
		free_command_data(data, 0);
	}

	write_command_history(data);
	free_command_data(data, 1);
	if (!interpret(data) && data->status)
		exit(data->status);
	if (builtin_return == -2)
	{
		if (data->error_number == -1)
			exit(data->status);
		exit(data->error_number);
	}

	return (builtin_return);
}

/**
 * find_builtin - Finds a built-in command
 * @data: The CommandData struct
 *
 * Return: -1 if built-in not found, 0 if built-in executed successfully,
 * 1 if built-in found but not successful, 2 if built-in signals exit()
 */
int find_builtin(CommandData *data)
{
	int j, builtin_return = -1;

	BuiltinCommandTable builtins[] = {
		{"exit", execute_exit},
		{"env", handle_environment},
		{"setenv", set_environment_variable},
		{"unsetenv", unset_environment_variable},
		{"cd", execute_cd},
		{"help", execute_help},
		{"history", execute_history},
		{"alias", execute_alias},
		{NULL, NULL}
	};/*deal with alias*/

	for (j = 0; builtins[j].type; j++)
	{
		if (compare_strings(data->argv[0], builtins[j].type) == 0)
		{
			data->line_counter++;
			builtin_return = builtins[j].function(data);
			break;
		}
	}
	return (builtin_return);

}

/**
 * find_command - Finds an executable command in PATH
 * @data: The CommandData struct
 *
 * Return: void
 */
void find_command(CommandData *data)
{
	char *path = NULL;
	int j, argument_num;

	data->path = data->argv[0];

	if (data->linecount_flag == 1)
	{
		data->line_counter++;
		data->linecount_flag = 0;
	}

	for (j = 0, argument_num = 0; data->arguments[j]; j++)
	{
		if (!is_delimiter(data->arguments[j], " \t\n"))
		{
			argument_num++;
		}
	}
	if (!argument_num)
	{
		return;
	}

	path = find_command_path(data, get_environment_variable(data, "PATH="),
			data->argv[0]);

	if (path)
	{
		data->path = path;
		fork_command(data);
	}
	else
	{
		if ((interpret(data) || get_environment_variable(data, "PATH=") ||
			 data->argv[0][0] == '/') && handle_command(data, data->argv[0]))
		{
			fork_command(data);
		}
		else if (*(data->arguments) != '\n')
		{
			data->status = 127;
			print_error_message_v2(data, "not found\n");
		}
	}
}

/**
 * fork_command - Forks a child process to run the command
 * @data: The CommandData struct
 *
 * Return: void
 */
void fork_command(CommandData *data)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error: Fork failed");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_custom_environment(data)) == -1)
		{
			free_command_data(data, 1);
			if (errno == EACCES)
			{
				exit(126);
			}
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
			{
				print_error_message_v2(data, "Permission denied\n");
			}
		}
	}
}

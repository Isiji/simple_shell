#include "shell.h"

/**
 * hsh - main shell loop
 * @data: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(data_t *data, char **av)
{
	ssize_t j = 0;
	int builtin_ret = 0;

	while (j != -1 && builtin_ret != -2)
	{
		clear_data(data);
		if (interactive(data))
			the_puts("$ ");
		the_eputchar(BUF_FLUSH);
		j = get_input(data);
		if (j != -1)
		{
			set_data(data, av);
			builtin_ret = find_builtin(data);
			if (builtin_ret == -1)
				find_cmd(data);
		}
		else if (interactive(data))
			the_putchar('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @data: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(data_t *data)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", the_exit},
		{"env", the_env},
		{"help", the_help},
		{"history", the_history},
		{"setenv", the_setenv},
		{"unsetenv", the_unsetenv},
		{"cd", the_cd},
		{"alias", the_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (the_strcmp(data->argv[0], builtintbl[i].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[i].func(data);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(data_t *data)
{
	char *path = NULL;
	int i, k;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, k = 0; data->arg[i]; i++)
		if (!is_delim(data->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(data, _getenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((interactive(data) || the_getenv(data, "PATH=")
					|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
			fork_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
		datao->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}

#include "blairs_simple_shell.h"


/**
 * execute_exit - Exits the shell
 * @data: Pointer to the CommandData struct
 *
 * Return: 0 if data.argv[0] != "exit"
 */
int execute_exit(CommandData *data)
{
	int exit_status;

	if (data->argv[1]) /* If there is an exit argument */
	{
		exit_status = custom_atoi(data->argv[1]);
		if (exit_status == -1)
		{
			data->status = 2;
			print_error_message_v2(data, "Illegal number: ");
			print_error_message(data->argv[1]);
			print_string_descriptor("\n", STDOUT_FILENO);
			return (1);
		}
		data->error_number = custom_atoi(data->argv[1]);
		return (-2);
	}
	data->error_number = -1;
	return (-2);
}


/**
 * execute_cd - Changes the current directory
 * @data: Pointer to the CommandData struct
 *
 * Return: Always 0
 */
int execute_cd(CommandData *data)
{
	char *current_directory, *new_directory, buffer[1024], **custom_env;
	int change_directory_result;

	current_directory = getcwd(buffer, 1024);
	if (!current_directory)
		print_error_message_v2(data, "getcwd failure\n");
	if (!data->argv[1])
	{
		char **env;

		new_directory = NULL;

		custom_env = get_custom_environment(data);
		if (custom_env)
		{
			for (env = custom_env; *env; env++)
			{
				if (startsWith(*env, "HOME="))
				{
					new_directory = *env + 5;
					break;
				}
			}
			free(custom_env);
		}
		if (new_directory)
			change_directory_result = chdir(new_directory);
		else
			change_directory_result = chdir("/");
	}
	else if (compare_strings(data->argv[1], "-") == 0)
	{
		new_directory = get_environment_variable(data, "OLDPWD=");
		if (!new_directory)
		{
			print_string(current_directory);
			print_string_descriptor("\n", STDOUT_FILENO);
			return (1);
		}
		print_string(new_directory), print_string_descriptor("\n", STDOUT_FILENO);
		change_directory_result = chdir(new_directory);
	}
	else
		change_directory_result = chdir(data->argv[1]);
	if (change_directory_result == -1)
	{
		print_error_message_v2(data, "can't cd to ");
		print_error_message(data->argv[1]);
		print_string_descriptor("\n", STDOUT_FILENO);
	}
	else
	{
		set_custom_environment_variable(data, "OLDPWD",
				get_environment_variable(data, "PWD="));
		set_custom_environment_variable(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * execute_help - Provides help information (not yet implemented)
 * @data: Pointer to the CommandData struct
 *
 * Return: Always 0
 */
int execute_help(CommandData *data)
{
	char **argument_array;

	argument_array = data->argv;
	print_string("help call works. Function not yet implemented \n");
	if (0)
		print_string(*argument_array); /* Temporary attribute_unused workaround */
	return (0);
}


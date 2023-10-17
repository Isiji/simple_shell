#include "blairs_simple_shell.h"


/**
 * execute_exit - Exits the shell
 * @data: Pointer to the CommandData struct
 *
 * Return: 0 if data.argv[0] != "exit"
 */
int execute_exit(CommandData *data)
{
	int ext_status;

	if (data->argv[1])
	{
		ext_status = custom_atoi(data->argv[1]);
		if (ext_status == -1)
		{
			data->status = 2;
			print_error_message_v2(data, "Illegal number: ");
			print_error_message(data->argv[1]);
			print_error_character('\n');
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
	char *curr_dir, *new_dir, buffer[1024], **custom_env;
	int change_dir_result;

	curr_dir = getcwd(buffer, 1024);
	if (!curr_dir)
		print_error_message_v2(data, "getcwd failure\n");
	if (!data->argv[1])
	{
		char **env;

		new_dir = NULL;

		custom_env = get_custom_environment(data);
		if (custom_env)
		{
			for (env = custom_env; *env; env++)
			{
				if (startsWith(*env, "HOME="))
				{
					new_dir = *env + 5;
					break;
				}
			}
			free(custom_env);
		}
		if (new_dir)
			change_dir_result = chdir(new_dir);
		else
			change_dir_result = chdir("/");
	}
	else if (compare_strings(data->argv[1], "-") == 0)
	{
		new_dir = get_environment_variable(data, "OLDPWD=");
		if (!new_dir)
		{
			print_string(curr_dir);
			print_string_descriptor("\n", STDOUT_FILENO);
			return (1);
		}
		print_string(new_dir), print_string_descriptor("\n", STDOUT_FILENO);
		change_dir_result = chdir(new_dir);
	}
	else
		change_dir_result = chdir(data->argv[1]);
	if (change_dir_result == -1)
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
	char **arg_array;

	arg_array = data->argv;
	print_string("help call works. Function not yet implemented \n");
	if (0)
		print_string(*arg_array); /* Temporary attribute_unused workaround */
	return (0);
}

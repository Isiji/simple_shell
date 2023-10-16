#include "shell.h"

/**
 *the_exit - exits the shell
 * @data: Structure containing arguments that maintain function prototype
 * Return: (0) if info.argv[0] != "exit"
 */
int the_exit(data_t *data)
{
	int excheck;

	if (data->argv[1]) /* If there is an exit arguement */
	{
		excheck = the_errtoi(data->argv[1]);
		if (excheck == -1)
		{
			data->status = 2;
			prt_err(data, "Illegal number: ");
			the_eputs(data->argv[1]);
			the_eputchar('\n');
			return (1);
		}
		data->err_num = the_errtoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * the_cd - changes the current directory
 * @data:contains arguments used to maintain constant function prototype.
 * Return: Always 0
 */
int the_cd(data_t *data)
{
	char *s, *dirn, buffer[1024];
	int chdirn_rn;

	s = getcwd(buffer, 1024);
	if (!s)
		the_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		dirn = the_getenv(data, "HOME=");
		if (!dirn)
			chdirn_rn = /* TODO: what should this be? */
				chdir((dirn = the_getenv(data, "PWD=")) ? dirn : "/");
		else
			chdirn_rn = chdir(dirn);
	}
	else if (the_strcmp(data->argv[1], "-") == 0)
	{
		if (!the_getenv(data, "OLDPWD="))
		{
			the_puts(s);
			the_putchar('\n');
			return (1);
		}
		the_puts(the_getenv(data, "OLDPWD=")), the_putchar('\n');
		chdirn_rn = /* TODO: what should this be? */
			chdir((dirn = the_getenv(data, "OLDPWD=")) ? dirn : "/");
	}
	else
		chdirn_rn = chdir(data->argv[1]);
	if (chdirn_rn == -1)
	{
		prt_err(data, "can't cd to ");
		the_eputs(data->argv[1]), the_eputchar('\n');
	}
	else
	{
		the_setenv(data, "OLDPWD", the_getenv(data, "PWD="));
		the_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * the_help - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int the_help(data_t *data)
{
	char **arg_array;

	arg_array = data->argv;
	the_puts("help call works. Function not yet implemented \n");
	if (0)
		the_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

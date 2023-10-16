#include "shell.h"

/**
 * clear_data - initializes info_t struct
 * @data: struct address
 */
void clear_data(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * set_data - initializes info_t struct
 * @data: struct address
 * @av: argument vector
 */
void set_data(data_t *data, char **av)
{
	int i = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = str_wrd(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = the_strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		rep_alias(data);
		replace_vars(data);
	}
}

/**
 * free_data - frees info_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void free_data(data_t *data, int all)
{
	free_str(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_node(&(data->env));
		if (data->history)
			free_node(&(data->history));
		if (data->alias)
			free_node(&(data->alias));
		free_str(data->environ);
			data->environ = NULL;
		free_p((void **)data->cmd_buf);
		if (data->readdt > 2)
			close(data->readdt);
		the_putchar(BUF_FLUSH);
	}
}

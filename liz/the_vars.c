#include "shell.h"

/**
 * the_chain - test if current char in buffer is a chain delimeter
 * @data: the parameter struct
 * @buf: the char buffer
 * @d: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int the_chain(data_t *data, char *buf, size_t *d)
{
	size_t j = *d;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*d = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @data: the parameter struct
 * @buf: the char buffer
 * @d: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(data_t *data, char *buf, size_t *d, size_t i, size_t len)
{
	size_t j = *d;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*d = j;
}

/**
 * rep_alias - replaces an aliases in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_alias(data_t *data)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = starts_with(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = the_strchr(node->str, '=');
		if (!p)
			return (0);
		p = the_strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(data_t *data)
{
	int i = 0;
	list_t *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;

		if (!the_strcmp(data->argv[i], "$?"))
		{
			replace_string(&(data->argv[i]),
					the_strdup(convert_num(data->status, 10, 0)));
			continue;
		}
		if (!the_strcmp(data->argv[i], "$$"))
		{
			replace_string(&(data->argv[i]),
					the_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = starts_with(data->env, &data->argv[i][1], '=');
		if (node)
		{
			replace_string(&(data->argv[i]),
					the_strdup(the_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->argv[i], the_strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @prev: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **prev, char *new)
{
	free(*prev);
	*prev = new;
	return (1);
}

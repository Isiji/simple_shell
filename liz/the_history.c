#include "shell.h"

/**
 * the_hist - gets the history file
 * @data: parameter struct
 *
 * Return: allocated string containg history file
 */

char *the_hist(data_t *data)
{
	char *buf, *dir;

	dir = the_getenv(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (the_strlen(dir) + the_strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	the_strcpy(buf, dir);
	the_strcat(buf, "/");
	the_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(data_t *data)
{
	ssize_t dt;
	char *filename = the_hist(data);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	dt = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (dt == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		the_putsdt(node->str, dt);
		the_putdt('\n', dt);
	}
	the_putdt(BUF_FLUSH, dt);
	close(dt);
	return (1);
}

/**
 * read_history - reads history from file
 * @data: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(data_t *data)
{
	int i, last = 0, linecount = 0;
	ssize_t dt, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = the_hist(data);

	if (!filename)
		return (0);

	dt = open(filename, O_RDONLY);
	free(filename);
	if (dt == -1)
		return (0);
	if (!fstat(dt, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(dt, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(dt);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history(data, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history(data, buf + last, linecount++);
	free(buf);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		delete_node(&(data->history), 0);
	renumber_history(data);
	return (data->histcount);
}

/**
 * build_history - adds entry to a history linked list
 * @data: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history(data_t *data, char *buf, int linecount)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	the_node_end(&node, buf, linecount);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @data: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(data_t *data)
{
	list_t *node = data->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (data->histcount = i);
}

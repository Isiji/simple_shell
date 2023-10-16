#include "shell.h"

/**
 * entry_buf - buffers chained commands
 * @data: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t entry_buf(data_t *data, char **buf, size_t *len)
{
	ssize_t j = 0;
	size_t len_k = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*free_p((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint);
#if USE_GETLINE
		j = getline(buf, &len_k, stdin);
#else
		j = the_getline(data, buf, &len_k);
#endif
		if (j > 0)
		{
			if ((*buf)[j - 1] == '\n')
			{
				(*buf)[j - 1] = '\0'; /* remove trailing newline */
				j--;
			}
			data->linecount_flag = 1;
			rem_comments(*buf);
			build_history(data, *buf, data->histcount++);
			/* if (the_strchr(*buf, ';')) is this a command chain? */
			{
				*len = j;
				data->cmd_buf = buf;
			}
		}
	}
	return (j);
}

/**
 * the_input - gets a line minus the newline
 * @data: parameter struct
 *
 * Return: bytes read
 */
ssize_t the_input(data_t *data)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(data->arg), *p;

	the_putchar(BUF_FLUSH);
	r = entry_buf(data, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain(data, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (the_chain(data, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			data->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (the_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @data: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(data_t *data, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(data->readdt, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * the_getline - gets the next line of input from STDIN
 * @data: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int the_getline(data_t *data, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(data, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = the_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = the_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		the_strncat(new_p, buf + i, k - i);
	else
		the_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint - blocks ctrl-C
 * @sig_count: the signal number
 *
 * Return: void
 */
void sigint(__attribute__((unused))int sig_count)
{
	the_puts("\n");
	the_puts("$ ");
	the_putchar(BUF_FLUSH);
}

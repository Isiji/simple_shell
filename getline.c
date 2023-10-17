#include "blairs_simple_shell.h"

/**
 * entry_buffer - buffers chained commands
 * @data: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t entry_buffer(CommandData *data, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handle_interrupt_signal);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = custom_getline(data, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			data->linecount_flag = 1;
			remove_comments_from_string(*buf);
			build_command_history(data, *buf, data->history_count++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			/*if (find_character_in_string(*buf, ';'))*/
			{
				*len = r;
				data->command_buffer = buf;
			}
		}
	}
	return (r);
}


/**
 * read_input - gets a line minus the newline
 * @data: parameter struct
 *
 * Return: bytes read
 */
ssize_t read_input(CommandData *data)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(data->arguments);
	char *p;

	print_character(BUFFER_FLUSH);

	r = entry_buffer(data, &buf, &len);

	if (r == -1)
		return (-1);

	if (len)
	{
		j = i;
		p = buf + i;

		check_command_chain(data, buf, &j, i, len);

		while (j < len)
		{
			if (is_command_chain(data, buf, &j))
				break;
			j++;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			data->command_buffer_type = NORMAL_COMMAND;
		}
		*buf_p = p;
		return (string_length(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buffer - reads a buffer
 * @data: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(CommandData *data, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);

	r = read(data->read_descriptor, buf, READ_BUFFER_SIZE);

	if (r >= 0)
		*i = r;

	return (r);
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @data: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int custom_getline(CommandData *data, char **ptr, size_t *length)
{
	static char buf[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;

	if (i == len)
		i = len = 0;

	r = read_buffer(data, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = find_character_in_string(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;

	new_p = reallocate_memory(p, s, s ? s + k : k + 1);

	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		concatenate_strings_with_length(new_p, buf + i, k - i);
	else
	{
		copy_string_with_length(new_p, buf + i, k - i + 1);
	}
	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;

	*ptr = p;
	return (s);
}

/**
 * handle_interrupt_signal - blocks ctrl-C
 * @signal_counter: the signal number
 * Return: void
 */
void handle_interrupt_signal(__attribute__((unused))int signal_counter)
{
	print_string("\n");
	print_string("$ ");
	print_character(BUFFER_FLUSH);
}


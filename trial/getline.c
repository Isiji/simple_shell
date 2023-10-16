#include "shell.h"
/**
 * my_getline - custom implementation of getline
 * @lineptr: pointer to a line of command or data
 * @n: number of chars
 * @stream: where the chars are
 * @fd: entries
 * Return: 0 on success
 */
ssize_t my_getline(char **lineptr, size_t *n, int fd)
{
	char c, *new_lineptr;
	size_t i = 0, new_size;
	ssize_t bytes_read;

	if (*lineptr == NULL || *n == 0)
	{
		*n = INITIAL_LINE_SIZE;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}
	while (1)
	{
		if (i >= *n - 1)
		{
		new_size = *n * 2;
		new_lineptr = (char *)realloc(*lineptr, new_size);
		if (new_lineptr == NULL)
		{
			return (-1);
		}
		*lineptr = new_lineptr;
		*n = new_size;
		}
		bytes_read = read(fd, &c, 1);

			if (bytes_read <= 0)
			{
				if (i == 0)
				{
					return (bytes_read);
				}
				break;
			}
		(*lineptr)[i] = c;
		i++;

		if (c == '\n')
		{
			break;
		}
	}
	(*lineptr)[i] = '\0';


	return (i);
}

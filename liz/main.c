#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 if successful, 1 if unsuccessful
 */
int main(int ac, char **av)
{
	data_t data[] = { DATA_INIT };
	int dt = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (dt)
			: "r" (dt));

	if (ac == 2)
	{
		dt = open(av[1], O_RDONLY);
		if (dt == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				the_eputs(av[0]);
				the_eputs(": 0: Can't open ");
				the_eputs(av[1]);
				the_eputchar('\n');
				the_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readdt = dt;
	}
	pop_envlist(data);
	read_history(data);
	hsh(data, av);
	return (EXIT_SUCCESS);
}

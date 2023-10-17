#include "blairs_simple_shell.h"

/**
 * main - The main entry point of the shell
 * @argc: The argument count
 * @argv: The argument vector
 *
 * Return: 0 if successful, 1 if unsuccessful
 */
int main(int argc, char **argv)
{
	CommandData data[] = { COMMAND_DATA_INIT };
	int file_descriptor = 2;


	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(file_descriptor)
		: "r"(file_descriptor));

if (argc == 2)
{
	file_descriptor = open(argv[1], O_RDONLY);
	if (file_descriptor == -1)
	{
		if (errno == EACCES)
		{
			exit(126);
		}
		if (errno == ENOENT)
		{
			print_string(argv[0]);
			print_string(": 0: Can't open ");
			print_string(argv[1]);
			print_character('\n');
			print_character(BUFFER_FLUSH);
			exit(127);
		}
		return (EXIT_FAILURE);
	}
	data->read_descriptor = file_descriptor;
}

pop_environment_list(data);
read_command_history(data);
shell_loop(data, argv);
return (EXIT_SUCCESS);
}


#include "shell.h"

/**
 * main - the main function of the project
 * @argc: number of urguments entered
 * @argv: variables 
 * Return: NULL
 */
int main(int argc, char *argv[])
{
	char *data = NULL;
	size_t data_size = 0;
	const char *pathenv = NULL;
	int file_descriptor, result;

	if (argc != 1 && argc != 2)
	{
		write(STDERR_FILENO, "Usage: ", 7);
		write(STDERR_FILENO, argv[0], the_strlen(argv[0]));
		write(STDERR_FILENO, "[file]\n", 8);
		return (EXIT_FAILURE);
	}
	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);

		if (file_descriptor == -1)
		{
			perror("Error opening file");
			return (EXIT_FAILURE);
		}
		while (my_getline(&data, &data_size, file_descriptor) != -1)
		{
			execution(data, pathenv);
		}
		close(file_descriptor);
	}

	while (1)
	{
		simple_prompt();

		if (my_getline(&data, &data_size, fileno(stdin)) == -1)
		{
			result = system(data);

			if (result == -1)
			{
				perror("Command execution failed");
			}
		}

			execution(data, pathenv);
	}

	free(data);

	return (EXIT_SUCCESS);

}

#include "shell.h"
/**
 * parse_and_store_path - goes through the path and stores it
 * @path: a pointer to the path list
 * @path_directories: stores a list of path directories
 */
void parse_and_store_path(char *path, char *path_directories[])
{
	char *token = my_strtok(path, ":");
	int i = 0;

	while (token != NULL && i < MAX_PATH_LENGTH)
	{
		path_directories[i] = the_strdup(token);
		token = my_strtok(NULL, ":");
			i++;
	}
	path_directories[i] = NULL;
}


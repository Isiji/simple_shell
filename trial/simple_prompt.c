#include "shell.h"
/**
 * simple_prompt - shows the prompt for data entry
 */
void simple_prompt(void)
{
	char *data = NULL;
	size_t bytes_read, data_size = 0;
	bool the_exit = false;
	const char *pathenv = getenv("PATH");
	int exit_status;

	while (!the_exit)
	{
		blizz("Home $ ");
		fflush(stdout);

		bytes_read = my_getline(&data, &data_size, STDIN_FILENO);

		if (bytes_read <= 0)
		{
			if (bytes_read == 0)
			{
				blizz("\n");
			}
			else
			{
				perror("my_getline");
			}
			break;
		}
		if (data[bytes_read - 1] == '\n')
		{
			data[bytes_read - 1] = '\0';
		}

		if (the_strcmp(data, "exit") == 0)
		{
			if (data[4] == '\0')
			{
				the_exit = true;
			}
			else
			{
				exit_status = convert_atoi(data + 5);

				my_exit(exit_status);
			}
		}
		else if (the_strcmp(data, "env") == 0)
		{
			my_env();
		}
		else
		{
			execution(data, pathenv);
		}
	}

	free(data);
	my_exit(EXIT_SUCCESS);
}

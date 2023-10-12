#include "shell.h"

/**
 * my_exit - exits the function or shell
 * @status: shows the exiting status code
 *
 * Exit: status
 */
void my_exit(int status)
{
	exit(status);
}


#include "shell.h"
/**
 * my_env - prints environmental variable currently
 *
 */
void my_env(void)
{
	extern char **environ;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		blizz(environ[i]);
		blizz("\n");
	}
}

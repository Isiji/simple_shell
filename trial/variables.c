#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "string.h"
/**
 * *intToString - shows the value of variable
 * @value: number of counts
 */
int lastExitStatus = 0;
pid_t currentPID;

char *intToString(int value)
{
	char *str;
	int temp = value;
	int length = 0;
	int i;

	while (temp != 0)
	{
		temp /= 10;
		length++;
	}

	if (value == 0)
	{
		length = 1;
	}

	str = (char *)malloc(length + 1);
	if (str == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	i = length - 1;

	while (value != 0)
	{
		int digit = value % 10;

		str[i] = digit + '0';
		value /= 10;
		i--;
	}
	str[length] = '\0';

	return (str);
}
/**
 * replaceVariables - function used to replace variables
 * @command: input used for replacement
 */
char *replaceVariables(char *command)
{
	char *result, *dest;

	result = (char *)malloc(strlen(command) * 2);
	if (result == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	dest = result;

	while (*command)
	{
		if (command[0] == '$' && command[1] == '?')
		{
			char *exitStatusStr = intToString(lastExitStatus);
			int exitStatusLength = strlen(exitStatusStr);

			strcpy(dest, exitStatusStr);
			dest += exitStatusLength;
			free(exitStatusStr);
			command += 2;
		}
		else if (command[0] == '$' && command[1] == '$')
		{
			char *pidStr = intToString(currentPID);
			int pidLength = strlen(pidStr);

			strcpy(dest, pidStr);
			dest += pidLength;
			free(pidStr);
			command += 2;
		}
		else
		{
			*dest++ = *command++;
		}
	}

	*dest = '\0';
	return (result);
}
/**
 * replaceExitStatus - function for replacing exit status
 * @args: first argument
 * @argc: number of arguments
 * @exitStatus: integer that enables exit
 */
void replaceExitStatus(char *args[], int argc, int exitStatus)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		if (strcmp(args[i], "$?") == 0)
		{
			char exitStatusStr[10];

			sprintf(exitStatusStr, "%d", exitStatus);
			free(args[i]);
			args[i] = strdup(exitStatusStr);
		}
	}
}
/**
 * replaceProcessID - function that replaces process ID
 * @args: first argument
 * @argc: number number of arguments
 */
void replaceProcessID(char *args[], int argc)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		if (strcmp(args[i], "$$") == 0)
		{
			char pidStr[10];

			sprintf(pidStr, "%d", getpid());
			free(args[i]);
			args[i] = strdup(pidStr);
		}
	}
}
/**
 * reconstructCommand - function that replace command with another
 * @replacedCommand: replacement character
 * @args: first argument
 * @argc: number of counts
 */
void reconstructCommand(char *replacedCommand, char *args[], int argc)
{
	int i;

	replacedCommand[0] = '\0';
	for (i = 0; i < argc; i++)
	{
		strcat(replacedCommand, args[i]);
		if (i < argc - 1)
			strcat(replacedCommand, " ");
	}
}

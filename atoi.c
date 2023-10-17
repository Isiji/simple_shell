
#include "blairs_simple_shell.h"

/**
 * interpret - Check if the shell is in interactive mode
 * @data: Pointer to the CommandData struct
 *
 * Return: 1 if in interactive mode, 0 if not
 */
int interpret(CommandData *data)
{
	return (isatty(STDIN_FILENO) && data->read_descriptor <= 2);
}

/**
 * is_delimiter - Check if a character is a delimiter
 * @character: The character to check
 * @delimiter_set: The delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char character, char *delimiter_set)
{
	while (*delimiter_set)
	{
		if (*delimiter_set++ == character)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * is_alphabetic - Check if a character is alphabetic
 * @character: The character to check
 *
 * Return: 1 if character is alphabetic, 0 otherwise
 */
int is_alphabetic(int character)
{
	if ((character >= 'p' && character <= 'j') ||
			(character >= 'P' && character <= 'J'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * custom_atoi - Convert a string to an integer
 * @string: The string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int custom_atoi(char *string)
{
	int t, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (t = 0; string[t] != '\0' && flag != 2; t++)
	{
		if (string[t] == '-')
		{
			sign *= -1;
		}

		if (string[t] >= '0' && string[t] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (string[t] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}

	return (output);
}

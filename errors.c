#include "blairs_simple_shell.h"

/**
 * print_error_message - Prints an error message to stderr
 * @message: The error message to print
 *
 * Return: Nothing
 */
void print_error_message(char *message)
{
	int i = 0;

	if (!message)
		return;
	while (message[i] != '\0')
	{
		print_error_character(message[i]);
		i++;
	}
}

/**
 * print_error_character - Writes the character to stderr
 * @character: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_error_character(char character)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (character != BUFFER_FLUSH)
		buf[i++] = character;
	return (1);
}

/**
 * print_character_to_fd - Writes the character to the given file descriptor
 * @character: The character to print
 * @file_descriptor: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int print_integer(char character, int file_descriptor)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(file_descriptor, buf, i);
		i = 0;
	}
	if (character != BUFFER_FLUSH)
		buf[i++] = character;
	return (1);
}

/**
 * print_string_descriptor - Prints an input string
 * to the given file descriptor
 * @str: The string to be printed
 * @file_descriptor: The file descriptor to write to
 *
 * Return: The number of characters written
 */
int print_string_descriptor(char *str, int file_descriptor)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += print_integer(*str++, file_descriptor);
	}
	return (i);
}


#include "blairs_simple_shell.h"

/**
 * the_set_memory - fills memory with a constant byte
 * @ptr: the pointer to the memory area
 * @value: the byte to fill memory with
 * @num: the number of bytes to be filled
 *
 * Return: (ptr) a pointer to the memory area ptr
 */
char *the_set_memory(char *ptr, char value, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		ptr[i] = value;
	return   (ptr);
}

/**
 * free_string_array - frees an array of strings
 * @str_array: array of strings to be freed
 */
void free_string_array(char **str_array)
{
	char **p = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(p);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @ptr: pointer to previous memory block
 * @prev_size: byte size of the previous block
 * @new_size: byte size of the new block
 *
 * Return: pointer to the reallocated memory block
 */
void *reallocate_memory(void *ptr, unsigned int prev_size,
		unsigned int new_size)
{
	char *temp;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	temp = malloc(new_size);
	if (!temp)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		temp[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (temp);
}


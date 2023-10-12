#includechar *the_memset(char *p, char b, unsigned int num) "shell.h"

/**
 * the_memset - fills memory with a constant byte
 * @p: the pointer to the memory area
 * @b: the byte to fill *s with
 * @num: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *the_memset(char *p, char b, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		p[i] = b;
	return (p);
}

/**
 * free_str - frees a string of strings
 * @sstr: string of strings
 */
void free_str(char **sstr)
{
	char **p = sstr;

	if (!sstr)
		return;
	while (*sstr)
		free(*sstr++);
	free(p);
}

/**
 * the_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *the_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *t;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	t = malloc(new_size);
	if (!t)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (t);
}

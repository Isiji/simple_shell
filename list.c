#include "blairs_simple_shell.h"


/**
 * create_list_node - creates a new node and
 * adds it at the beginning of the list
 * @head_pointer: address of the pointer to the head node
 * @string: string for the new node
 * @number: node index used by history
 *
 * Return: Allocated list node
 */
StringList *create_list_node(StringList **head_pointer, const char *str,
		int number)
{
	StringList *new_node;

	if (!head_pointer)
		return (NULL);

	new_node = malloc(sizeof(StringList));

	if (!new_node)
		return (NULL);
	fill_memory_with_character((void *)new_node, 0, sizeof(StringList));

	new_node->number = number;

	if (str)
	{
		new_node->str = duplicate_string(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head_pointer;
	*head_pointer = new_node;

	return (new_node);
}

/**
 * create_list_node_at_end - creates a new node and
 * adds it at the end of the list
 * @head_pointer: address of the pointer to the head node
 * @string: string for the new node
 * @number: node index used by history
 *
 * Return: Allocated list node
 */
StringList *create_list_node_at_end(StringList **head_pointer,
		const char *str, int number)
{
	StringList *new_node, *node;

	if (!head_pointer)
		return (NULL);

	node = *head_pointer;
	new_node = malloc(sizeof(StringList));

	if (!new_node)
		return (NULL);

	fill_memory_with_character((void *)new_node, 0, sizeof(StringList));
	new_node->number = number;

	if (str)
	{
		new_node->str = duplicate_string(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
	{
		*head_pointer = new_node;
	}

	return (new_node);
}

/**
 * print_list_strings - prints the strings of a linked list
 * @head: pointer to the head node
 *
 * Return: the number of nodes in the list
 */
size_t print_list_strings(const StringList *head)
{
	size_t size = 0;

	while (head)
	{
		print_string(head->str ? head->str : "(nil)");
		print_string("\n");
		head = head->next;
		size++;
	}

	return (size);
}

/**
 * delete_list_node - deletes a node at a given index
 * @head_pointer: address of the pointer to the head node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_list_node(StringList **head_pointer, unsigned int index)
{
	StringList *node, *prev_node;
	unsigned int i = 0;

	if (!head_pointer || !*head_pointer)
		return (0);

	if (!index)
	{
		node = *head_pointer;
		*head_pointer = (*head_pointer)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *head_pointer;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_list_node - frees all nodes of a linked list
 * @head_pointer: address of the pointer to the head node
 *
 * Return: void
 */
void free_list_node(StringList **head_pointer)
{
	StringList *node, *next_node, *current_head;

	if (!head_pointer || !*head_pointer)
		return;

	current_head = *head_pointer;
	node = current_head;

	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*head_pointer = NULL;
}


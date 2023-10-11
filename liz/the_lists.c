#include "shell.h"

/**
 * the_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @s: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *the_node(list_t **head, const char *s, int num)
{
	list_t *n_head;

	if (!head)
		return (NULL);
	n_head = malloc(sizeof(list_t));
	if (!n_head)
		return (NULL);
	the_memset((void *)n_head, 0, sizeof(list_t));
	n_head->num = num;
	if (s)
	{
		n_head->s = the_strdup(s);
		if (!n_head->s)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->next = *head;
	*head = n_head;
	return (n_head);
}

/**
 * the_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @s: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *the_node_end(list_t **head, const char *s, int num)
{
	list_t *n_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	n_node = malloc(sizeof(list_t));
	if (!n_node)
		return (NULL);
	the_memset((void *)n_node, 0, sizeof(list_t));
	n_node->num = num;
	if (s)
	{
		n_node->s = the_strdup(s);
		if (!n_node->s)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = n_node;
	}
	else
		*head = n_node;
	return (n_node);
}

/**
 * the_list_str - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t the_list_str(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		the_puts(head->str ? head->str : "(nil)");
		the_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * delete_node - deletes node at given index
 * @h address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node(list_t **h, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		node = *h;
		*h = (*h)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *h;
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
 * free_node - frees all nodes of a list
 * @head_p: address of pointer to head node
 *
 * Return: void
 */
void free_node(list_t **head_p)
{
	list_t *node, *next_node, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_p = NULL;
}

#include <stdlib.h>

#include "list-generic-c.h"

static List_node *list_node_new(void)
{
	return malloc(sizeof(List_node));
}

/* Initialize an empty list. */
void list_init(List *list)
{
	list->head = NULL;
}

/* Free a list, optionally freeing the data using the free_data function. */
void list_free(List *list, void (*free_data)(void *))
{
	List_node *p, *next;

	for (p = list->head; p != NULL; p = next) {
		next = p->next;
		if (free_data != NULL)
			free_data(p->data);
		free(p);
	}
}

/* Get the first node of the list, or NULL if the list is empty. */
List_node *list_head(const List *list)
{
	return list->head;
}

/* Return the size of the list. */
unsigned int list_size(const List *list)
{
	const List_node *p;
	unsigned int count;

	count = 0;
	for (p = list->head; p != NULL; p = p->next)
		count++;

	return count;
}

/* Insert a node containing data at the front of a list. Return the node
   inserted. */
List_node *list_insert(List *list, void *data)
{
	List_node *new_node;

	new_node = list_node_new();
	if (new_node == NULL)
		return NULL;
	new_node->data = data;
	new_node->next = list->head;
	list->head = new_node;

	return new_node;
}

/* Return node if node is a node in list, NULL otherwise. */
const List_node *list_lookup(const List *list, const List_node *node)
{
	const List_node *p;

	for (p = list->head; p != NULL; p = p->next) {
		if (p == node)
			return p;
	}

	return NULL;
}

/* Return the first node containing data if there is one in the list, NULL
   otherwise. */
List_node *list_lookup_data(const List *list, const void *data,
	int (*cmp)(const void *, const void *))
{
	List_node *p;

	for (p = list->head; p != NULL; p = p->next) {
		if (cmp(p->data, data) == 0)
			return p;
	}

	return NULL;
}

/* Delete a node from a list. Return the node deleted, or NULL if it was not
   present. */
List_node *list_delete(List *list, List_node *node)
{
	List_node *p, *prev;

	prev = NULL;
	for (p = list->head; p != NULL; p = p->next) {
		if (p == node) {
			if (prev == NULL)
				list->head = p->next;
			else
				prev->next = p->next;
			return p;
		}
	}

	return NULL;
}

/* Delete the first node containing data from a list. Return the node deleted,
   or NULL if no such node was found. */
List_node *list_delete_data(List *list, const void *data,
	int (*cmp)(const void *, const void *))
{
	List_node *p, *prev;

	prev = NULL;
	for (p = list->head; p != NULL; p = p->next) {
		if (cmp(p->data, data) == 0) {
			if (prev == NULL)
				list->head = p->next;
			else
				prev->next = p->next;
			return p;
		}
	}

	return NULL;
}

#ifndef _LIST_GENERIC_C_H
#define _LIST_GENERIC_C_H

typedef struct List_node List_node;
struct List_node {
	void *data;
	List_node *next;
};

typedef struct List List;
struct List {
	struct List_node *head;
};

void list_init(List *list);
void list_free(List *list, void (*free_data)(void *));
List_node *list_head(const List *list);
unsigned int list_size(const List *list);
List_node *list_insert(List *list, void *data);
const List_node *list_lookup(const List *list, const List_node *node);
List_node *list_lookup_data(const List *list, const void *data,
	int (*cmp)(const void *, const void *));
List_node *list_delete(List *list, List_node *node);
List_node *list_delete_data(List *list, const void *data,
	int (*cmp)(const void *, const void *));

#endif

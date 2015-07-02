#include <stdio.h>
#include <string.h>

#include "list-generic-c.h"

#define check(c) { printf("%s %s\n", c ? "passed: " : "FAILED: ", #c); }

static int cmp_string(const void *a, const void *b)
{
	return strcmp(a, b);
}

int main(int argc, char *argv[])
{
	List list;
	List_node *abc;

	list_init(&list);

	check(list_size(&list) == 0);
	list_insert(&list, "abc");
	check(list_size(&list) == 1);
	abc = list_lookup_data(&list, "abc", cmp_string);
	check(abc != NULL);
	check(list_lookup(&list, abc) == abc);
	check(list_lookup_data(&list, "def", cmp_string) == NULL);
	check(cmp_string((char *) list_head(&list)->data, "abc") == 0);
	list_insert(&list, "def");
	check(list_size(&list) == 2);
	check(cmp_string((char *) list_head(&list)->data, "def") == 0);
	list_delete(&list, abc);
	check(list_lookup_data(&list, "abc", cmp_string) == NULL);
	list_delete_data(&list, "def", cmp_string);
	check(list_size(&list) == 0);

	list_free(&list, NULL);

	return 0;
}

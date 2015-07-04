/* Representation of character classes for regular expressions */
/* A class is a sorted linked list of ranges */

#include <stdlib.h>

#include "charclass.h"
#include "eprintf.h"
#include "utf8.h"

struct charclass_node {
	Rune start;
	Rune end;
	struct charclass_node *next;
};

void charclass_free(struct charclass *cc)
{
	struct charclass_node *p, *next;

	if (cc == NULL)
		return;
	for (p = cc->head; p != NULL; p = next) {
		next = p->next;
		free(p);
	}
	free(cc);
}

/* charclass_add: add the range [start-end] to class */
struct charclass *charclass_add(struct charclass *cc, Rune start, Rune end)
{
	struct charclass_node *p, *prev;

	if (start > end)
		return cc;

	p = cc->head;
	prev = NULL;
	while (p != NULL && start > p->end + 1) {
		prev = p;
		p = p->next;
	}
	if (p == NULL || end < p->start - 1) {
		struct charclass_node *node;

		node = emalloc(sizeof(*node));
		node->start = start;
		node->end = end;
		node->next = p;
		if (prev == NULL)
			cc->head = node;
		else
			prev->next = node;
	} else {
		/* consolidate following nodes */
		while (p->next != NULL && end >= p->next->start - 1) {
			struct charclass_node *next = p->next;
			p->next = next->next;
			if (next->end > end)
				end = next->end;
			free(next);
		}
		if (start < p->start)
			p->start = start;
		if (end > p->end)
			p->end = end;
	}

	return cc;
}

int charclass_has(struct charclass *cc, Rune c)
{
	struct charclass_node *p;

	for (p = cc->head; p != NULL; p = p->next) {
		if (c >= p->start && c <= p->end)
			return 1;
	}

	return 0;
}

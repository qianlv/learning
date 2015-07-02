#ifndef _CHARCLASS_H
#define _CHARCLASS_H

#include "utf8.h"

struct charclass_node;

struct charclass {
	struct charclass_node *head;
};

void charclass_free(struct charclass *cc);

struct charclass *charclass_add(struct charclass *cc, Rune start, Rune end);

int charclass_has(struct charclass *cc, Rune c);

#endif

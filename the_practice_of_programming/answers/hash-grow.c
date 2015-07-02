#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "eprintf.h"

enum { MULTIPLIER = 31, MAX_AVG_CHAIN_LENGTH = 2, SYMTAB_GROWTH_FACTOR = 2 };

typedef struct Nameval Nameval;
struct Nameval {
	char	*name;
	int	value;
	Nameval	*next;	/* in chain */
};
Nameval **symtab = NULL;	/* a symbol table */
/* the size of the symbol table */
unsigned int nhash = 10;
/* how many items in the symbol table */
unsigned int nitems = 0;

/* hash_mod: compute hash value of string between 0 and nhash */
unsigned int hash_mod(char *str, unsigned int nhash)
{
	unsigned int h;
	unsigned char *p;

	h = 0;
	for (p = (unsigned char *) str; *p != '\0'; p++)
		h = MULTIPLIER * h + *p;

	return h % nhash;
}

/* hash: compute hash value of string between 0 and nhash */
unsigned int hash(char *str)
{
	return hash_mod(str, nhash);
}

/* lookup: find a name in symtab, with optional create */
Nameval *lookup(char *name, int create, int value)
{
	int h;
	Nameval *sym;

	/* initialize the hash table if necessary */
	if (symtab == NULL) {
		int i;

		symtab = emalloc(nhash * sizeof(Nameval *));
		for (i = 0; i < nhash; i++)
			symtab[i] = NULL;
	}

	h = hash(name);
	for (sym = symtab[h]; sym != NULL; sym = sym->next)
		if (strcmp(name, sym->name) == 0)
			return sym;
	if (create) {
		sym = (Nameval *) emalloc(sizeof(Nameval));
		sym->name = name;	/* assumed allocated elsewhere */
		sym->value = value;
		sym->next = symtab[h];
		symtab[h] = sym;
		nitems++;
	}

	/* grow the hash table if it gets too full */
	if ((double) nitems / nhash > MAX_AVG_CHAIN_LENGTH) {
		Nameval **new_symtab;
		unsigned int new_nhash;
		int i;
		Nameval *sym, *next;

		new_nhash = nhash * SYMTAB_GROWTH_FACTOR;
		new_symtab = emalloc(new_nhash * sizeof(Nameval *));
		for (i = 0; i < new_nhash; i++)
			new_symtab[i] = NULL;
		for (i = 0; i < nhash; i++) {
			for (sym = symtab[i]; sym != NULL; sym = next) {
				next = sym->next;
				h = hash_mod(sym->name, new_nhash);
				sym->next = new_symtab[h];
				new_symtab[h] = sym;
			}
		}
		free(symtab);
		symtab = new_symtab;
		nhash = new_nhash;
	}

	return sym;
}

/* count: count the number of entries in symtab */
int count(void)
{
	int i, count;
	Nameval *p;

	count = 0;
	for (i = 0; i < nhash; i++) {
		for (p = symtab[i]; p != NULL; p = p->next)
			count++;
	}

	return count;
}

/* random_string: fill a char array with a random string of length len */
static char *random_string(char *s, int len)
{
	int i;
	char c;

	for (i = 0; i < len; i++) {
		do {
			c = rand() % 128;
		} while (!isprint(c));
		s[i] = c;
	}
	s[i] = '\0';

	return s;
}

enum { INSERT_NUM = 1000 };

int main(int argc, char *argv[])
{
	int i;

	i = 0;
	for (;;) {
		char string[10];

		printf("%u/%u = %.2f\n", nitems, nhash, (double) nitems / nhash);
		if (i >= INSERT_NUM)
			break;
		random_string(string, sizeof(string));
		lookup(strdup(string), 1, i);
		i++;
		if (count() != i) {
			eprintf("error growing hash: expected %d entries, found %d.\n",
				i, count());
		}
	}

	return 0;
}

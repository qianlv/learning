#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "eprintf.h"

enum { MULTIPLIER = 31, NHASH = 127 };

typedef struct Nameval Nameval;
struct Nameval {
	char	*name;
	int	value;
	Nameval	*next;	/* in chain */
};
Nameval *symtab[NHASH];	/* a symbol table */

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

/* hash: compute hash value of string between 0 and NHASH */
unsigned int hash(char *str)
{
	return hash_mod(str, NHASH);
}

/* lookup: find a name in symtab, with optional create */
Nameval *lookup(char *name, int create, int value)
{
	int h;
	Nameval *sym;

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
	}
	return sym;
}

/* apply: execute fn for each element of symtab, in arbitrary order */
void apply(void (*fn)(Nameval*, void*), void *arg)
{
	int i;
	Nameval *sym;

	for (i = 0; i < NHASH; i++) {
		for (sym = symtab[i]; sym != NULL; sym = sym->next)
			fn(sym, arg);
	}
}

/* printnv: print name and value using format in arg */
static void printnv(Nameval *sym, void *arg)
{
	printf((const char *) arg, sym->name, sym->value);
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

/* fill_symtab: build a sample hash table for testing */
static void fill_symtab(void)
{
	lookup("smiley", 1, 0x263A);
	lookup("Aacute", 1, 0x00C1);
	lookup("AElig", 1, 0x00C6);
	lookup("Acirc", 1, 0x00C2);
	lookup("zeta", 1, 0x03B6);
}

enum { MAX_MULTIPLE = 3, MAX_STRING_LENGTH = 15 };

/* trivial_collisions: show strings that hash to the same value starting from a
   base character. */
static void trivial_collisions(char base)
{
	char string[MAX_STRING_LENGTH + 1];
	int i;
	int h, r;
	unsigned int n;

	h = (int) base % NHASH;
	n = 0;
	for (i = 0; i < MAX_STRING_LENGTH; i++) {
		r = h - n % NHASH;
		if (r < 0)
			r += NHASH;
		/* don't print garbage strings */
		if (!isprint(r))
			break;
		string[i] = (char) r;
		string[i + 1] = '\0';
		n += r;
		n *= MULTIPLIER;
		h = hash(string);
		printf("hash(\"%s\") = %u\n", string, h);
	}
}

/* nhash_collisions: show the collisions that can occur when the final
   character of strings are fixed and NHASH is a multiple of MULTIPLIER. */
static void nhash_collisions(void)
{
	char string[MAX_STRING_LENGTH + 1];
	int i, m;

	for (m = 1; m <= MAX_MULTIPLE; m++) {
		for (i = 0; i < MAX_STRING_LENGTH - 1; i++) {
			random_string(string, i);
			string[i] = '$';
			string[i + 1] = '\0';
			printf("hash_mod(\"%s\", %d * MULTIPLIER) = %u\n",
				string, m, hash_mod(string, m * MULTIPLIER));
		}
		if (m < MAX_MULTIPLE)
			printf("\n");
	}
}

int main(int argc, char *argv[])
{
	char c;

	srand(time(NULL));

	printf("Collisions when NHASH is a multiple of MULTIPLIER.\n");
	nhash_collisions();

	printf("\n");

	printf("Trivial collisions (only printable strings shown).\n");
	for (c = 'a'; c <= 'm'; c++)
		trivial_collisions(c);

	printf("\n");

	fill_symtab();

	apply(printnv, "%s: %04X\n");

	return 0;
}

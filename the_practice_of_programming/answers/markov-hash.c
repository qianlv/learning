/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 3-2 */

/*
 * Markov chain random text generator.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "eprintf.h"

enum {
	NPREF	= 2,	/* number of prefix words */
	NHASH	= 4093,	/* size of state hash table array */
	MAXGEN	= 10000,/* maximum words generated */
	NHASH_STR	= 8191	/* size of string hash table array */
};

typedef struct State State;
typedef struct Suffix Suffix;
typedef struct Suffix String;

struct State {	/* prefix + suffix list */
	char	*pref[NPREF];	/* prefix words */
	Suffix	*suf;			/* list of suffixes */
	State	*next;			/* next in hash table */
};

struct Suffix {	/* list of suffixes */
	char	*word;			/* suffix */
	Suffix	*next;			/* next in list of suffixes */
};

State	*lookup(char *prefix[], int create);
void	build(char *prefix[], FILE*);
void	generate(int nwords);
void	add(char *prefix[], char *word);

char	*lookup_string(char *s);

void print_memory_use(void);

State	*statetab[NHASH];	/* hash table of states */
String	*stringtab[NHASH_STR];	/* hash table of strings */

char NONWORD[] = "\n";  /* cannot appear as real word */

/* markov-hash main: markov-chain random text generation */
int main(void)
{
	int i, nwords = MAXGEN;
	char *prefix[NPREF];		/* current input prefix */

	int c;
	long seed;

	setprogname("markov-hash");
	/* seed = time(NULL); */
	seed = 0;

	srand(seed);
	for (i = 0; i < NPREF; i++)	/* set up initial prefix */
		prefix[i] = NONWORD;
	build(prefix, stdin);
	add(prefix, NONWORD);
	generate(nwords);
	print_memory_use();
	return 0;
}   

const int MULTIPLIER = 31;  /* for hash() */

/* hash: compute hash value for array of NPREF strings. Assumes that identical
   strings have identical addresses. */
unsigned int hash(char *s[NPREF])
{
	unsigned int h;
	int i;

	h = 0;
	for (i = 0; i < NPREF; i++)
		h = (h * MULTIPLIER) ^ (((unsigned long) s[i]) >> 1);
	return h % NHASH;
}

/* lookup: search for prefix; create if requested. */
/*  returns pointer if present or created; NULL if not. */
/*  creation doesn't strdup so strings mustn't change later. */
/*  assumes that identical strings have identical addresses. */
State* lookup(char *prefix[NPREF], int create)
{
	int i, h;
	State *sp;

	h = hash(prefix);
	for (sp = statetab[h]; sp != NULL; sp = sp->next) {
		for (i = 0; i < NPREF; i++)
			if (prefix[i] != sp->pref[i])
				break;
		if (i == NPREF)		/* found it */
			return sp;
	}
	if (create) {
		sp = (State *) emalloc(sizeof(State));
		for (i = 0; i < NPREF; i++)
			sp->pref[i] = prefix[i];
		sp->suf = NULL;
		sp->next = statetab[h];
		statetab[h] = sp;
	}
	return sp;
}

/* addsuffix: add to state. suffix must not change later */
void addsuffix(State *sp, char *suffix)
{
	Suffix *suf;

	suf = (Suffix *) emalloc(sizeof(Suffix));
	suf->word = suffix;
	suf->next = sp->suf;
	sp->suf = suf;
}

/* add: add word to suffix list, update prefix */
void add(char *prefix[NPREF], char *suffix)
{
	State *sp;

	sp = lookup(prefix, 1);  /* create if not found */
	addsuffix(sp, suffix);
	/* move the words down the prefix */
	memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
	prefix[NPREF-1] = suffix;
}

/* build: read input, build prefix table */
void build(char *prefix[NPREF], FILE *f)
{
	char buf[100], fmt[10];

	/* create a format string; %s could overflow buf */
	sprintf(fmt, "%%%ds", sizeof(buf)-1);
	while (fscanf(f, fmt, buf) != EOF)
		add(prefix, lookup_string(buf));
}

/* generate: produce output, one word per line */
void generate(int nwords)
{
	State *sp;
	Suffix *suf;
	char *prefix[NPREF], *w;
	int i, nmatch;

	for (i = 0; i < NPREF; i++)	/* reset initial prefix */
		prefix[i] = NONWORD;

	for (i = 0; i < nwords; i++) {
		sp = lookup(prefix, 0);
		if (sp == NULL)
			eprintf("internal error: lookup failed");
		nmatch = 0;
		for (suf = sp->suf; suf != NULL; suf = suf->next)
			if (rand() % ++nmatch == 0) /* prob = 1/nmatch */
				w = suf->word;
		if (nmatch == 0)
			eprintf("internal error: no suffix %d %s", i, prefix[0]);
		if (strcmp(w, NONWORD) == 0)
			break;
		printf("%s\n", w);
		memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
		prefix[NPREF-1] = w;
	}
}

/* hash_string: compute hash value for string */
unsigned int hash_string(const char *s)
{
	unsigned int h;

	h = 0;
	for ( ; *s != '\0'; s++)
		h = MULTIPLIER * h + *s;

	return h % NHASH_STR;
}

/* lookup_string: look up a string in the string hash table. Always inserts the
   string if it doesn't exist. */
char *lookup_string(char *s)
{
	String *p;
	int h;

	h = hash_string(s);
	for (p = stringtab[h]; p != NULL; p = p->next)
		if (strcmp(s, p->word) == 0)
			return p->word;
	p = emalloc(sizeof(String));
	p->word = estrdup(s);
	p->next = stringtab[h];
	stringtab[h] = p;

	return p->word;
}

void print_memory_use(void)
{
	size_t statetab_size = 0;
	size_t stringtab_size = 0;
	size_t state_size = 0;
	size_t suffix_size = 0;
	size_t string_size = 0;
	size_t strings_size = 0;
	int i;
	State *statep;
	Suffix *suffixp;
	String *stringp;

	statetab_size = sizeof(statetab);
	for (i = 0; i < NHASH; i++) {
		for (statep = statetab[i]; statep != NULL; statep = statep->next) {
			state_size += sizeof(*statep);
			for (suffixp = statep->suf; suffixp != NULL; suffixp = suffixp->next)
				suffix_size += sizeof(*suffixp);
		}
	}
	stringtab_size = sizeof(stringtab);
	for (i = 0; i < NHASH_STR; i++) {
		for (stringp = stringtab[i]; stringp != NULL; stringp = stringp->next) {
			string_size += sizeof(*stringp);
			strings_size += strlen(stringp->word) + 1;
		}
	}

	printf("Size of state hash table: %u bytes.\n", (unsigned int) statetab_size);
	printf("Size of string hash table: %u bytes.\n", (unsigned int) stringtab_size);
	printf("Size of State structures: %u bytes.\n", (unsigned int) state_size);
	printf("Size of Suffix structures: %u bytes.\n", (unsigned int) suffix_size);
	printf("Size of String structures: %u bytes.\n", (unsigned int) string_size);
	printf("Size of all strings: %u bytes.\n", (unsigned int) strings_size);
	printf("Total %u bytes.\n", (unsigned int) (statetab_size + stringtab_size
		+ state_size + suffix_size + string_size + strings_size));
}

/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 3-3 */

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
	MAXGEN	= 10000	/* maximum words generated */
};

typedef struct State State;
typedef struct Suffix Suffix;

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
void	build(char *initialprefix[], char *finalprefix[NPREF], FILE*);
void	generate(char *initialprefix[], char *finalprefix[NPREF], int nwords);
void	add(char *prefix[], char *word);

State	*statetab[NHASH];	/* hash table of states */

/* markov-nosentinel main: markov-chain random text generation */
int main(void)
{
	int i, nwords = MAXGEN;
	char *initialprefix[NPREF];	/* first NPREF words of input */
	char *finalprefix[NPREF];	/* last NPREF words of input */

	int c;
	long seed;

	setprogname("markov-nosentinel");
	seed = time(NULL);

	srand(seed);
	/* here NULL is not a sentinel (it does not go in the hash table), */
	/* rather it is a mark to record the length of the initial prefix */
	for (i = 0; i < NPREF; i++)
		initialprefix[i] = NULL;
	build(initialprefix, finalprefix, stdin);
	for (i = 0; i < NPREF && initialprefix[i] != NULL; i++)
		printf("%s\n", initialprefix[i]);
	/* generate only if we have enough input. */
	if (i == NPREF)
		generate(initialprefix, finalprefix, nwords - NPREF);
	return 0;
}   

const int MULTIPLIER = 31;  /* for hash() */

/* hash: compute hash value for array of NPREF strings */
unsigned int hash(char *s[NPREF])
{
	unsigned int h;
	unsigned char *p;
	int i;

	h = 0;
	for (i = 0; i < NPREF; i++)
		for (p = (unsigned char *) s[i]; *p != '\0'; p++)
			h = MULTIPLIER * h + *p;
	return h % NHASH;
}

/* lookup: search for prefix; create if requested. */
/*  returns pointer if present or created; NULL if not. */
/*  creation doesn't strdup so strings mustn't change later. */
State* lookup(char *prefix[NPREF], int create)
{
	int i, h;
	State *sp;

	h = hash(prefix);
	for (sp = statetab[h]; sp != NULL; sp = sp->next) {
		for (i = 0; i < NPREF; i++)
			if (strcmp(prefix[i], sp->pref[i]) != 0)
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

/* build: read input, build prefix table, store initial and
   final prefixes. */
void build(char *initialprefix[NPREF], char *finalprefix[NPREF], FILE *f)
{
	char buf[100], fmt[10];
	char *word;
	int count = 0;

	/* create a format string; %s could overflow buf */
	sprintf(fmt, "%%%ds", sizeof(buf)-1);
	while (fscanf(f, fmt, buf) != EOF) {
		word = estrdup(buf);
		if (count < NPREF) {
			/* prime the prefix array */
			initialprefix[count] = finalprefix[count] = word;
			count++;
		} else {
			add(finalprefix, word);
		}
	}

	return;
}

/* generate: produce output, one word per line */
void generate(char *initialprefix[NPREF], char *finalprefix[NPREF], int nwords)
{
	State *sp;
	Suffix *suf;
	char *prefix[NPREF], *w;
	int i, j, nmatch;

	for (i = 0; i < NPREF; i++)	/* set initial prefix */
		prefix[i] = initialprefix[i];

	for (i = 0; i < nwords; i++) {
		sp = lookup(prefix, 0);
		if (sp == NULL)
			/* no suffix for this prefix, must be the end */
			break;
		nmatch = 0;
		for (suf = sp->suf; suf != NULL; suf = suf->next)
			if (rand() % ++nmatch == 0) /* prob = 1/nmatch */
				w = suf->word;
		if (nmatch == 0)
			eprintf("internal error: no suffix %d %s", i, prefix[0]);
		/* check for final prefix, give a chance to quit */
		for (j = 0; j < NPREF; j++)
			if (strcmp(prefix[j], finalprefix[j]) != 0)
				break;
		if (j == NPREF && rand() % (nmatch + 1) == 0)
			break;
		printf("%s\n", w);
		memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
		prefix[NPREF-1] = w;
	}
}

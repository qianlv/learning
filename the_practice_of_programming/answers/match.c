/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercises 9-8, 9-9, 9-10, 9-11, 9-12, and 9-13 */

#include <stdlib.h>
#include "charclass.h"
#include "eprintf.h"
#include "utf8.h"

enum re_atom_type {
	CHAR,
	DOT,
	STAR,
	PLUS,
	QUEST,
	CARET,
	DOLLAR,
	CLASS,
	NEGCLASS,
};

struct re_atom {
	enum re_atom_type type;
	union {
		Rune c;	/* CHAR */
		struct charclass *cc;	/* CLASS, NEGCLASS */
	} u;
	struct re_atom *next;
};

struct re {
	struct re_atom *head;
};

struct re *compile(char*);
void	freeregexp(struct re*);
int	match(struct re*, char*, int*, int*);
int	matchhere(struct re_atom*, char*, int, int*);
int	matchstar(struct re_atom*, struct re_atom*, char*, int, int*);
int	matchplus(struct re_atom*, struct re_atom*, char*, int, int*);
int	matchquest(struct re_atom*, struct re_atom*, char*, int, int*);

/* compile_charclass_range: get next start-end range */
/* on error either *start or *end will be UTF8_BADCHAR */
static char *compile_charclass_range(char *regexp, Rune *start, Rune *end)
{
	char *next;
	Rune c;

	*start = UTF8_BADCHAR;
	*end = UTF8_BADCHAR;

	regexp += utf8_to_rune(&c, regexp);

	if (c == UTF8_BADCHAR)
		return regexp;
	if (c == '\\') {
		next = regexp + utf8_to_rune(&c, regexp);
		if (c == UTF8_BADCHAR)
			return next;
		if (c == '\0')
			c = '\\';
		else
			regexp = next;
	}
	*start = c;

	next = regexp + utf8_to_rune(&c, regexp);
	if (c == '-') {
		next += utf8_to_rune(&c, next);
		if (c == UTF8_BADCHAR)
			return next;
		if (c == '\\') {
			regexp = next;
			next = regexp + utf8_to_rune(&c, regexp);
			if (c == UTF8_BADCHAR)
				return next;
			if (c == '\0')
				c = '\\';
			else
				regexp = next;
			*end = c;
		} else if (c != '\0' && c != ']') {
			*end = c;
			regexp = next;
		} else {
			*end = *start;
		}
	} else {
		*end = *start;
	}

	return regexp;
}

/* compile_charclass: compile a "[abc]" character class */
/* presumes that "[" or "[^" has been handled already */
char *compile_charclass(char *regexp, struct charclass **cc)
{
	char *next;
	Rune c;

	*cc = emalloc(sizeof(**cc));
	(*cc)->head = NULL;

	next = regexp + utf8_to_rune(&c, regexp);
	/* in the first position, ']' means a literal ']' */
	if (c == ']') {
		charclass_add(*cc, c, c);
		regexp = next;
	}
	while (utf8_to_rune(&c, regexp), c != '\0' && c != ']') {
		Rune start, end;

		regexp = compile_charclass_range(regexp, &start, &end);
		if (start == UTF8_BADCHAR || end == UTF8_BADCHAR) {
			weprintf("invalid character in character class");
			charclass_free(*cc);
			*cc = NULL;
			return regexp;
		}

		charclass_add(*cc, start, end);
	}
	if (c != ']') {
		weprintf("unmatched [");
		charclass_free(*cc);
		*cc = NULL;
		return regexp;
	}
	regexp += utf8_to_rune(&c, regexp);

	return regexp;
}

/* compile: turn regexp string into a list of re_atom */
struct re *compile(char *regexp)
{
	struct re *result;
	struct re_atom **prev_next;
	struct re_atom *atom;
	char *next;
	Rune c;

	result = emalloc(sizeof(*result));
	result->head = NULL;
	prev_next = &result->head;

	while (regexp += utf8_to_rune(&c, regexp), c != '\0') {
		atom = emalloc(sizeof(*atom));
		atom->next = NULL;
		*prev_next = atom;
		prev_next = &atom->next;
		switch (c) {
		case '.':
			atom->type = DOT;
			break;
		case '*':
			atom->type = STAR;
			break;
		case '+':
			atom->type = PLUS;
			break;
		case '?':
			atom->type = QUEST;
			break;
		case '^':
			atom->type = CARET;
			break;
		case '$':
			atom->type = DOLLAR;
			break;
		case '[':
			next = regexp + utf8_to_rune(&c, regexp);
			if (c == '\0') {
				atom->type = CHAR;
				atom->u.c = '[';
			} else if (c == '^') {
				atom->type = NEGCLASS;
				regexp = compile_charclass(next, &atom->u.cc);
				if (atom->u.cc == NULL) {
					freeregexp(result);
					return NULL;
				}
			} else {
				atom->type = CLASS;
				regexp = compile_charclass(regexp, &atom->u.cc);
				if (atom->u.cc == NULL) {
					freeregexp(result);
					return NULL;
				}
			}
			break;
		case '\\':
			atom->type = CHAR;
			regexp += utf8_to_rune(&c, regexp);
			if (c == '\0')
				atom->u.c = '\\';
			else
				atom->u.c = c;
			break;
		case UTF8_BADCHAR:
			freeregexp(result);
			return NULL;
			break;
		default:
			atom->type = CHAR;
			atom->u.c = c;
			break;
		}
	}

	return result;
}

/* freeregexp: free compiled regexp */
void freeregexp(struct re *regexp)
{
	struct re_atom *p, *next;

	if (regexp == NULL)
		return;
	for (p = regexp->head; p != NULL; p = next) {
		next = p->next;
		if (p->type == CLASS)
			charclass_free(p->u.cc);
		free(p);
	}
	free(regexp);
}

/* re_atom_match: match a character against an re_atom */
int re_atom_match(struct re_atom *atom, Rune c)
{
	if (c == UTF8_BADCHAR)
		return 0;

	if (atom->type == DOT)
		return 1;
	else if (atom->type == CHAR)
		return c == atom->u.c;
	else if (atom->type == CLASS)
		return charclass_has(atom->u.cc, c);
	else if (atom->type == NEGCLASS)
		return !charclass_has(atom->u.cc, c);

	return 0;
}

/* matchhere: search for regexp at pos */
int matchhere(struct re_atom *regexp, char *text, int pos, int *end)
{
	int nextpos;
	Rune c;

	if (regexp == NULL) {
		*end = pos;
		return 1;
	}

	if (regexp->next != NULL && regexp->next->type == STAR)
		return matchstar(regexp, regexp->next->next, text, pos, end);
	if (regexp->next != NULL && regexp->next->type == PLUS)
		return matchplus(regexp, regexp->next->next, text, pos, end);
	if (regexp->next != NULL && regexp->next->type == QUEST)
		return matchquest(regexp, regexp->next->next, text, pos, end);
	if (regexp->type == CARET)
		return pos == 0 && matchhere(regexp->next, text, pos, end);

	nextpos = pos + utf8_to_rune(&c, text + pos);
	if (regexp->type == DOLLAR)
		return c == '\0' && matchhere(regexp->next, text, pos, end);
	if (c != '\0' && re_atom_match(regexp, c))
		return matchhere(regexp->next, text, nextpos, end);

	return 0;
}

/* match: search for regexp anywhere in text */
/* start and end count bytes, not characters */
int match(struct re *regexp, char *text, int *start, int *end)
{
	Rune c;
	*start = 0;
	do {	/* must look even if string is empty */
		if (matchhere(regexp->head, text, *start, end))
			return 1;
		*start += utf8_to_rune(&c, text + *start);
	} while (c != '\0');
	return 0;
}

/* matchstar: leftmost longest search for atom*regexp */
int matchstar(struct re_atom *atom, struct re_atom *regexp, char *text, int pos, int *end)
{
	int nextpos;
	Rune c;

	nextpos = pos + utf8_to_rune(&c, text + pos);
	if (c != '\0' && re_atom_match(atom, c) && matchstar(atom, regexp, text, nextpos, end))
		return 1;
	return matchhere(regexp, text, pos, end);
}

/* matchplus: search for atom+regexp at beginning of text */
int matchplus(struct re_atom *atom, struct re_atom *regexp, char *text, int pos, int *end)
{
	int nextpos;
	Rune c;

	nextpos = pos + utf8_to_rune(&c, text + pos);
	/* "a+" is like "aa*" */
	return c != '\0' && re_atom_match(atom, c) && matchstar(atom, regexp, text, nextpos, end);
}

/* matchquest: leftmost longest search for atom?regexp */
int matchquest(struct re_atom *atom, struct re_atom *regexp, char *text, int pos, int *end)
{
	int nextpos;
	Rune c;

	nextpos = pos + utf8_to_rune(&c, text + pos);
	if (c != '\0' && re_atom_match(atom, c) && matchhere(regexp, text, nextpos, end))
		return 1;
	return matchhere(regexp, text, pos, end);
}

/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 4-2 */
/* This version allows fields to be separated by a regular expression */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "csv.h"

enum { NOMEM = -2 };          /* out of memory signal */

static char *line    = NULL;  /* input chars */
static char *sline   = NULL;  /* line copy used by split */
static int  maxline  = 0;     /* size of line[] and sline[] */
static char **field  = NULL;  /* field pointers */
static int  maxfield = 0;     /* size of field[] */
static int  nfield   = 0;     /* number of fields in field[] */

static char *DEFAULT_SEPARATOR = " *, *"; /* field separator regular expression */
static struct re *sep_regexp = NULL; /* compiled regular expression */

struct re *compile(char*);
void	freeregexp(struct re*);
int	match(struct re*, char*, int*, int*);

static char *advquoted(char *, char **);
static int split(void);
int csvfieldsep(char *sep);

/* endofline: check for and consume \r, \n, \r\n, or EOF */
static int endofline(FILE *fin, int c)
{
	int eol;

	eol = (c=='\r' || c=='\n');
	if (c == '\r') {
		c = getc(fin);
		if (c != '\n' && c != EOF)
			ungetc(c, fin);	/* read too far; put c back */
	}
	return eol;
}

/* reset: set variables back to starting values */
static void reset(void)
{
	free(line);	/* free(NULL) permitted by ANSI C */
	free(sline);
	free(field);
	line = NULL;
	sline = NULL;
	field = NULL;
	maxline = maxfield = nfield = 0;
}

/* csvgetline:  get one line, grow as needed */
/* sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625 */
char *csvgetline(FILE *fin)
{	
	int i, c;
	char *newl, *news;

	if (line == NULL) {			/* allocate on first call */
		maxline = maxfield = 1;
		line = (char *) malloc(maxline);
		sline = (char *) malloc(maxline);
		field = (char **) malloc(maxfield*sizeof(field[0]));
		if (line == NULL || sline == NULL || field == NULL) {
			reset();
			return NULL;		/* out of memory */
		}
	}
	if (sep_regexp == NULL) {
		if (csvfieldsep(DEFAULT_SEPARATOR) == -1) {
			reset();
			return NULL;
		}
	}
	for (i=0; (c=getc(fin))!=EOF && !endofline(fin,c); i++) {
		if (i >= maxline-1) {	/* grow line */
			maxline *= 2;		/* double current size */
			newl = (char *) realloc(line, maxline);
			if (newl == NULL) {
				reset();
				return NULL;
			}
			line = newl;
			news = (char *) realloc(sline, maxline);
			if (news == NULL) {
				reset();
				return NULL;
			}
			sline = news;


		}
		line[i] = c;
	}
	line[i] = '\0';
	if (split() == NOMEM) {
		reset();
		return NULL;			/* out of memory */
	}
	return (c == EOF && i == 0) ? NULL : line;
}

/* matchpattern:  return the first place in s where pattern matches, or NULL if
   there is no match. If end is not NULL, store the end of the match there. */
static char *matchpattern(char *s, struct re *regexp, char **end)
{
	int matched, p, q;

	matched = match(regexp, s, &p, &q);
	if (matched) {
		if (end != NULL)
			*end = s + q;
		return s + p;
	} else {
		return NULL;
	}
}

/* split: split line into fields */
static int split(void)
{
	char *p, **newf;
	char *sepp; /* pointer to temporary separator character */
	char *end;  /* end of regular expression match */
	int sepc;   /* temporary separator character */

	nfield = 0;
	if (line[0] == '\0')
		return 0;
	strcpy(sline, line);
	p = sline;

	do {
		if (nfield >= maxfield) {
			maxfield *= 2;			/* double current size */
			newf = (char **) realloc(field, 
						maxfield * sizeof(field[0]));
			if (newf == NULL)
				return NOMEM;
			field = newf;
		}
		if (*p == '"')
			sepp = advquoted(++p, &end);	/* skip initial quote */
		else {
			sepp = matchpattern(p, sep_regexp, &end);
			if (sepp == NULL)
				sepp = strchr(p, '\0');
		}
		sepc = sepp[0];
		sepp[0] = '\0';				/* terminate field */
		field[nfield++] = p;
		p = end;
	} while (sepc != '\0');

	return nfield;
}

/* advquoted: quoted field; return pointer to next separator */
static char *advquoted(char *p, char **end)
{
	int i, j;

	for (i = j = 0; p[j] != '\0'; i++, j++) {
		if (p[j] == '"' && p[++j] != '"') {
			/* copy up to next separator or \0 */
			int k;
			char *s = matchpattern(p+j, sep_regexp, end);
			if (s == NULL)
				s = strchr(p+j, '\0');
			k = s-(p+j);
			memmove(p+i, p+j, k);
			i += k;
			j += k;
			break;
		}
		p[i] = p[j];
	}
	p[i] = '\0';
	return p + j;
}

/* csvfieldsep:  set the field separator pattern, return -1 on error */
int csvfieldsep(char *sep)
{
	freeregexp(sep_regexp);
	sep_regexp = compile(sep);
	if (sep_regexp == NULL)
		return -1;
	return 0;
}

/* csvfield:  return pointer to n-th field */
char *csvfield(int n)
{
	if (n < 0 || n >= nfield)
		return NULL;
	return field[n];
}

/* csvnfield:  return number of fields */ 
int csvnfield(void)
{
	return nfield;
}

/* csvtest main: test CSV library */
int main(void)
{
	int i;
	char *line;

	while ((line = csvgetline(stdin)) != NULL) {
		printf("line = `%s'\n", line);
		for (i = 0; i < csvnfield(); i++)
			printf("field[%d] = `%s'\n", i, csvfield(i));
	}
	return 0;
}

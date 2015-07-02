/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 4-1 */

/* This implementation uses the strategy of splitting lines only up to the field
   requested. */

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
static char *fieldp  = NULL;  /* remainder of line after split fields */

static char fieldsep[] = ","; /* field separator chars */

static char *advquoted(char *);
static int split(int n);

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
	fieldp = NULL;
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
	strcpy(sline, line);
	fieldp = sline;
	nfield = 0;
	return (c == EOF && i == 0) ? NULL : line;
}

/* split: split line into up to n fields */
static int split(int n)
{
	char *p, **newf;
	char *sepp; /* pointer to temporary separator character */
	int sepc;   /* temporary separator character */

	if (n <= nfield)
		return nfield;
	if (*fieldp == '\0')
		return nfield;
	p = fieldp;

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
			sepp = advquoted(++p);	/* skip initial quote */
		else
			sepp = p + strcspn(p, fieldsep);
		sepc = sepp[0];
		sepp[0] = '\0';				/* terminate field */
		field[nfield++] = p;
		p = sepp + 1;
	} while (sepc == ',' && nfield < n);
	fieldp = p;

	return nfield;
}

/* advquoted: quoted field; return pointer to next separator */
static char *advquoted(char *p)
{
	int i, j;

	for (i = j = 0; p[j] != '\0'; i++, j++) {
		if (p[j] == '"' && p[++j] != '"') {
			/* copy up to next separator or \0 */
			int k = strcspn(p+j, fieldsep);
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

/* csvfield:  return pointer to n-th field */
char *csvfield(int n)
{
	if (split(n + 1) == NOMEM) {
		reset();
		return NULL;			/* out of memory */
	}
	if (n < 0 || n >= nfield)
		return NULL;
	return field[n];
}

/* csvnfield:  return number of fields */ 
int csvnfield(void)
{
	int n;

	n = nfield;
	while (*fieldp != '\0') {
		if (split(n + 1) == NOMEM) {
			reset();
			return -1;			/* out of memory */
		}
		n++;
	}

	return n;
}

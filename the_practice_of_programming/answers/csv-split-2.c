/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 4-1 */

/* This implementation uses the strategy of splitting only the requested
   field. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "csv.h"

enum { NOMEM = -2 };          /* out of memory signal */

static char *line    = NULL;  /* input chars */
static char *sline   = NULL;  /* line copy used by split */
static int  maxline  = 0;     /* size of line[] */
static int  maxsline = 0;     /* size of sline[] */

static char fieldsep[] = ","; /* field separator chars */

static char *skip_field(char *p);
static char *sline_grow(int n);
static char *copyquoted(char *p);

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
	line = NULL;
	sline = NULL;
	maxline = maxsline = 0;
}

/* csvgetline:  get one line, grow as needed */
/* sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625 */
char *csvgetline(FILE *fin)
{	
	int i, c;
	char *newl;

	if (line == NULL) {			/* allocate on first call */
		maxline = 1;
		line = (char *) malloc(maxline);
		if (line == NULL) {
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
		}
		line[i] = c;
	}
	line[i] = '\0';
	return (c == EOF && i == 0) ? NULL : line;
}

/* skip_field: return a pointer to the field following the one where p
   points */
static char *skip_field(char *p)
{
	if (*p == '"') {
		for (p++; *p != '\0'; p++) {
			if (*p == '"' && *(++p) != '"') {
				p += strcspn(p, fieldsep);
				break;
			}
		}
	} else {
		p += strcspn(p, fieldsep);
	}
	if (*p == ',')
		p++;
	return p;
}

/* sline_grow: make sure sline can hold at least n characters plus a \0
   terminator. Return NULL on error. */
static char *sline_grow(int n)
{
	char *news;

	if (maxsline == 0)
		maxsline = 1;
	while (maxsline < n + 1)
		maxsline *= 2;
	news = (char *) realloc(sline, maxsline);
	if (news == NULL) {
		reset();
		return NULL;
	}
	sline = news;

	return sline;
}

/* copyquoted: quoted field; copy to sline */
static char *copyquoted(char *p)
{
	int i, j;

	for (i = j = 0; p[j] != '\0'; i++, j++) {
		if (p[j] == '"' && p[++j] != '"') {
			/* copy up to next separator or \0 */
			int k = strcspn(p+j, fieldsep);
			if (sline_grow(i + k) == NULL) {
				reset();
				return NULL;
			}
			memmove(sline+i, p+j, k);
			i += k;
			j += k;
			break;
		}
		if (sline_grow(i) == NULL) {
			reset();
			return NULL;
		}
		sline[i] = p[j];
	}
	sline[i] = '\0';

	return sline;
}

/* csvfield:  return pointer to n-th field */
char *csvfield(int n)
{
	char *p;
	int k;

	if (n < 0)
		return NULL;

	p = line;
	while (n > 0) {
		p = skip_field(p);
		if (*p == '\0')
			return NULL;
		n--;
	}

	if (*p == '"') {
		if (copyquoted(++p) == NULL)
			return NULL;
	} else {
		k = strcspn(p, fieldsep);
		if (sline_grow(strcspn(p + k, fieldsep)) == NULL)
			return NULL;
		memmove(sline, p, k);
		sline[k] = '\0';
	}

	return sline;
}

/* csvnfield:  return number of fields */ 
int csvnfield(void)
{
	char *p;
	int n;

	n = 0;
	p = line;
	while (*p != '\0') {
		p = skip_field(p);
		n++;
	}

	return n;
}

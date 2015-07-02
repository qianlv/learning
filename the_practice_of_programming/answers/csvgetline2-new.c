/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 4-8 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

enum { NOMEM = -2 };          /* out of memory signal */

struct csv {
	char *line;      /* input chars */
	char *sline;     /* line copy used by split */
	int  maxline;    /* size of line[] and sline[] */
	char **field;    /* field pointers */
	int  maxfield;   /* size of field[] */
	int  nfield;     /* number of fields in field[] */
};

static char fieldsep[] = ","; /* field separator chars */

static char *advquoted(char *);
static int split(struct csv *);

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
static void reset(struct csv *csv)
{
	free(csv->line);	/* free(NULL) permitted by ANSI C */
	free(csv->sline);
	free(csv->field);
	csv->line = NULL;
	csv->sline = NULL;
	csv->field = NULL;
	csv->maxline = csv->maxfield = csv->nfield = 0;
}

/* csvnew:  initialize a struct csv */
void csvnew(struct csv *csv)
{
	csv->line = NULL;
	csv->sline = NULL;
	csv->maxline = 0;
	csv->field = NULL;
	csv->maxfield = 0;
	csv->nfield = 0;
}

/* csvgetline:  get one line, grow as needed */
/* sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625 */
char *csvgetline(struct csv *csv, FILE *fin)
{	
	int i, c;
	char *newl, *news;

	if (csv->line == NULL) {			/* allocate on first call */
		csv->maxline = csv->maxfield = 1;
		csv->line = (char *) malloc(csv->maxline);
		csv->sline = (char *) malloc(csv->maxline);
		csv->field = (char **) malloc(csv->maxfield*sizeof(csv->field[0]));
		if (csv->line == NULL || csv->sline == NULL || csv->field == NULL) {
			reset(csv);
			return NULL;		/* out of memory */
		}
	}
	for (i=0; (c=getc(fin))!=EOF && !endofline(fin,c); i++) {
		if (i >= csv->maxline-1) {	/* grow line */
			csv->maxline *= 2;		/* double current size */
			newl = (char *) realloc(csv->line, csv->maxline);
			if (newl == NULL) {
				reset(csv);
				return NULL;
			}
			csv->line = newl;
			news = (char *) realloc(csv->sline, csv->maxline);
			if (news == NULL) {
				reset(csv);
				return NULL;
			}
			csv->sline = news;


		}
		csv->line[i] = c;
	}
	csv->line[i] = '\0';
	if (split(csv) == NOMEM) {
		reset(csv);
		return NULL;			/* out of memory */
	}
	return (c == EOF && i == 0) ? NULL : csv->line;
}

/* split: split line into fields */
static int split(struct csv *csv)
{
	char *p, **newf;
	char *sepp; /* pointer to temporary separator character */
	int sepc;   /* temporary separator character */

	csv->nfield = 0;
	if (csv->line[0] == '\0')
		return 0;
	strcpy(csv->sline, csv->line);
	p = csv->sline;

	do {
		if (csv->nfield >= csv->maxfield) {
			csv->maxfield *= 2;			/* double current size */
			newf = (char **) realloc(csv->field, 
						csv->maxfield * sizeof(csv->field[0]));
			if (newf == NULL)
				return NOMEM;
			csv->field = newf;
		}
		if (*p == '"')
			sepp = advquoted(++p);	/* skip initial quote */
		else
			sepp = p + strcspn(p, fieldsep);
		sepc = sepp[0];
		sepp[0] = '\0';				/* terminate field */
		csv->field[csv->nfield++] = p;
		p = sepp + 1;
	} while (sepc == ',');

	return csv->nfield;
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
char *csvfield(struct csv *csv, int n)
{
	if (n < 0 || n >= csv->nfield)
		return NULL;
	return csv->field[n];
}

/* csvnfield:  return number of fields */ 
int csvnfield(struct csv *csv)
{
	return csv->nfield;
}

/* csvtest main: test CSV library */
int main(void)
{
	int i;
	char *line;
	struct csv csv;

	csvnew(&csv);
	while ((line = csvgetline(&csv, stdin)) != NULL) {
		printf("line = `%s'\n", line);
		for (i = 0; i < csvnfield(&csv); i++)
			printf("field[%d] = `%s'\n", i, csvfield(&csv, i));
	}
	return 0;
}

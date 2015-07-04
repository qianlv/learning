/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 9-12 */

#include <stdio.h>
#include <string.h>
#include "eprintf.h"

struct re;
struct re *compile(char*);
void	freeregexp(struct re*);
int	match(struct re*, char*, int*, int*);
int gres(struct re*, char*, FILE*, char*);

int main(int argc, char *argv[])
{
	struct re *regexp;
	int i, nrepl;
	FILE *f;

	setprogname("gres");
	if (argc < 3)
		eprintf("usage: gres regexp replacement [file ...]");
	regexp = compile(argv[1]);
	if (regexp == NULL)
		eprintf("can't compile regular expression");
	nrepl = 0;
	if (argc == 3) {
		nrepl += gres(regexp, argv[2], stdin, NULL);
	} else {
		for (i = 3; i < argc; i++) {
			f = fopen(argv[i], "r");
			if (f == NULL) {
				weprintf("can't open %s:", argv[i]);
				continue;
			}
			nrepl += gres(regexp, argv[2], f, argc>4 ? argv[i] : NULL);
			fclose(f);
		}
	}
	freeregexp(regexp);
	return nrepl > 0;
}

/* grep: replace regexp in file */
int gres(struct re *regexp, char *repl, FILE *f, char *name)
{
	int i, n, nrepl;
	char buf[BUFSIZ], *p;

	nrepl = 0;
	while (fgets(buf, sizeof buf, f) != NULL) {
		int start, end;

		if (name != NULL)
			printf("%s:", name);
		n = strlen(buf);
		if (n > 0 && buf[n-1] == '\n')
			buf[n-1] = '\0';
		p = buf;
		while (match(regexp, p, &start, &end)) {
			nrepl++;
			for (i = 0; i < start; i++)
				putchar(p[i]);
			printf("%s", repl);
			p += end;
		}
		printf("%s\n", p);
	}
	return nrepl;
}

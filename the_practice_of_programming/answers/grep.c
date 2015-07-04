/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercises 9-8 and 9-10 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "eprintf.h"

struct re;
struct re *compile(char*);
void	freeregexp(struct re*);
int	match(struct re*, char*, int*, int*);
int	grep(struct re*, FILE*, char*);

static int invert = 0;
static int count_only = 0;
static int line_numbers = 0;

/* grep main: search for regexp in files */
int main(int argc, char *argv[])
{
	int i, o, nmatch;
	struct re *regexp;
	FILE *f;

	setprogname("grep");
	while ((o = getopt(argc, argv, "cnv")) != -1) {
		switch (o) {
			case 'c':
				count_only = 1;
				break;
			case 'n':
				line_numbers = 1;
				break;
			case 'v':
				invert = 1;
				break;
			case '?':
			default:
				/* getopt prints an error message */
				exit(2);
				break;
		}

	}
	if (optind == argc)
		eprintf("usage: grep regexp [file ...]");
	nmatch = 0;
	regexp = compile(argv[optind]);
	if (regexp == NULL)
		eprintf("can't compile regular expression");
	if (argc - optind == 1) {
		if (grep(regexp, stdin, NULL))
			nmatch++;
	} else {
		for (i = optind + 1; i < argc; i++) {
			f = fopen(argv[i], "r");
			if (f == NULL) {
				weprintf("can't open %s:", argv[i]);
				continue;
			}
			if (grep(regexp, f, argc - optind>2 ? argv[i] : NULL) > 0)
				nmatch++;
			fclose(f);
		}
	}
	freeregexp(regexp);
	return nmatch == 0;
}

/* grep: search for regexp in file */
int grep(struct re *regexp, FILE *f, char *name)
{
	int n, matched, nmatch;
	long lineno;
	char buf[BUFSIZ];

	nmatch = 0;
	lineno = 0;
	while (fgets(buf, sizeof buf, f) != NULL) {
		int start, end;

		lineno++;
		n = strlen(buf);
		if (n > 0 && buf[n-1] == '\n')
			buf[n-1] = '\0';
		matched = match(regexp, buf, &start, &end);
		if (invert)
			matched = !matched;
		if (matched) {
			nmatch++;
			if (!count_only) {
				if (name != NULL)
					printf("%s:", name);
				if (line_numbers)
					printf("%ld:", lineno);
				printf("%s\n", buf);
			}
		}
	}
	if (count_only) {
		if (name != NULL)
			printf("%s:", name);
		printf("%d\n", nmatch);
	}
	return nmatch;
}

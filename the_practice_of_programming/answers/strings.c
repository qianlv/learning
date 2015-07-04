/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 5-2 */

#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "eprintf.h"

void strings(char *, FILE *);

static int minlen = 6;

/* strings main: find printable strings in files */
int main(int argc, char *argv[])
{
	int i, o;
	FILE *fin;

	setprogname("strings");
	while ((o = getopt(argc, argv, "n:")) != -1) {
		char *tail;
		switch (o) {
			case 'n':
				errno = 0;
				minlen = strtol(optarg, &tail, 10);
				if (errno != 0 || *tail != '\0' || minlen <= 0)
					eprintf("Bad argument to -n (\"%s\"); use a positive integer.", optarg);
				break;
			case '?':
			default:
				/* getopt prints an error message */
				exit(1);
				break;
		}
	}
	if (optind == argc)
		eprintf("usage: strings [-n min] filenames");
	else {
		for (i = optind; i < argc; i++) {
			if ((fin = fopen(argv[i], "rb")) == NULL)
				weprintf("can't open %s:", argv[i]);
			else {
				strings(argv[i], fin);
				fclose(fin);
			}
		}
	}
	return 0;
}

/* strings: extract printable strings from stream */
void strings(char *name, FILE *fin)
{
	int c, i;
	char buf[BUFSIZ];

	do {	/* once for each string */
		for (i = 0; (c = getc(fin)) != EOF; ) {
			if (!isprint(c))
				break;
			buf[i++] = c;
			if (i >= BUFSIZ)
				break;
		}
		if (i >= minlen) /* print if long enough */
			printf("%s:%.*s\n", name, i, buf);
	} while (c != EOF);
}

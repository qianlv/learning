#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "eprintf.h"

static int maxwidth = 0;
static int show_nonprinting = 1;

/* vis:  copy input to output, making non-printing characters visible */
static void vis(char *name, FILE *fin, FILE *fout)
{
	int c;
	int column = 0;

	while ((c = getc(fin)) != EOF) {
		if (isprint(c) || c == '\n') {
			if (c == '\n') {
				putc(c, fout);
				column = 0;
			} else {
				if (maxwidth != 0 && column >= maxwidth) {
					putc('\n', fout);
					column = 0;
				}
				putc(c, fout);
				column++;
			}
		} else if (show_nonprinting) {
			char buf[10], *p = buf;
			sprintf(buf, "\\X%02X", c);
			if (maxwidth != 0) {
				while (column + strlen(p) > maxwidth) {
					fprintf(fout, "%.*s\n", maxwidth - column, p);
					p += maxwidth - column;
					column = 0;
				}
			}
			column += fprintf(fout, "%s", p);
		}
	}
}

int main(int argc, char *argv[])
{
	int i, o;

	setprogname("vis");
	while ((o = getopt(argc, argv, "hw:x")) != -1) {
		switch (o) {
			char *tail;
			case 'h':
				printf("usage: vis [-w width] [-x] [filenames]\n");
				exit(0);
				break;
			case 'w':
				errno = 0;
				maxwidth = strtol(optarg, &tail, 10);
				if (errno != 0 || *tail != '\0' || maxwidth < 0)
					eprintf("Bad argument to -w (\"%s\"); use a non-negative integer.", optarg);
				break;
			case 'x':
				show_nonprinting = 0;
				break;
			case '?':
			default:
				/* getopt prints an error message */
				exit(1);
				break;
		}
	}
	if (optind == argc) {
		vis("<stdin>", stdin, stdout);
	} else {
		for (i = optind; i < argc; i++) {
			FILE *fin;

			if ((fin = fopen(argv[i], "rb")) == NULL) {
				weprintf("can't open %s:", argv[i]);
			} else {
				vis(argv[i], fin, stdout);
				fclose(fin);
			}
		}
	}

	return 0;
}

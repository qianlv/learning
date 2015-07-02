#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eprintf.h"

const char *pat[] = {
	"Make millions in your spare time",
	"XXX-rated",
	"buy!",
	"big bucks",
	"best pictures",
};

#define NPAT (sizeof(pat) / sizeof(pat[0]))
#define NSTART 10

int patlen[NPAT];			/* length of pattern */
int starting[UCHAR_MAX+1][NSTART];	/* pats starting with char */
int nstarting[UCHAR_MAX+1];		/* number of such patterns */

/* spaminit: initialize data structures for pattern matching */
void spaminit(void)
{
	int i;
	unsigned char c;

	for (i = 0; i < NPAT; i++) {
		c = pat[i][0];
		if (nstarting[c] >= NSTART)
			eprintf("too many patterns (>=%d) begin '%c'",
				NSTART, c);
		starting[c][nstarting[c]++] = i;
		patlen[i] = strlen(pat[i]);
	}
}

/* isspam: test mesg for occurrence of any pat */
int isspam(char *mesg)
{
	int i, j, k;
	unsigned char c;

	for (j = 0; (c = mesg[j]) != '\0'; j++) {
		for (i = 0; i < nstarting[c]; i++) {
			k = starting[c][i];
			if (memcmp(mesg+j, pat[k], patlen[k]) == 0) {
				printf("spam: match for '%s'\n", pat[k]);
				return 1;
			}
		}
	}
	return 0;
}

static char *read_mesg(FILE *fp)
{
	char buf[BUFSIZ];
	char *mesg = NULL, *p;
	size_t len = 0, n;

	while ((n = fread(buf, 1, sizeof(buf), fp)) != 0) {
		p = realloc(mesg, len + n + 1);
		if (p == NULL) {
			free(mesg);
			return NULL;
		}
		mesg = p;
		memcpy(mesg + len, buf, n);
		len += n;
	}
	mesg[len] = '\0';

	return mesg;
}

int main(void)
{
	char *mesg;

	setprogname("spam-1");

	spaminit();
	mesg = read_mesg(stdin);
	if (mesg == NULL)
		eprintf("Could not read message.");
	if (isspam(mesg))
		printf("spam\n");
	else
		printf("not spam\n");
	free(mesg);

	return 0;
}

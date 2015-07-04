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
#define NSTART 4
#define PREFIX_LEN 2

/* length of pattern */
int patlen[NPAT];
/* pats starting with two-char prefix */
int starting[UCHAR_MAX+1][UCHAR_MAX+1][NSTART];
/* number of such patterns */
int nstarting[UCHAR_MAX+1][UCHAR_MAX+1];

/* spaminit: initialize data structures for pattern matching */
void spaminit(void)
{
	int i;
	unsigned char c[PREFIX_LEN+1];

	for (i = 0; i < NPAT; i++) {
		strncpy((char *) c, pat[i], sizeof(c));
		if (nstarting[c[0]][c[1]] >= NSTART)
			eprintf("too many patterns (>=%d) begin '%c%c'",
				NSTART, c[0], c[1]);
		starting[c[0]][c[1]][nstarting[c[0]][c[1]]++] = i;
		patlen[i] = strlen(pat[i]);
	}
}

/* isspam: test mesg for occurrence of any pat */
int isspam(char *mesg)
{
	int i, j, k;
	unsigned char c[PREFIX_LEN];
	int n;

	n = 0;
	memset(c, 0, sizeof(c));
	for (j = 0; (c[n] = mesg[j]) != '\0'; j++) {
		for (i = 0; i < nstarting[c[0]][c[1]]; i++) {
			k = starting[c[0]][c[1]][i];
			if (memcmp(mesg+j-n, pat[k], patlen[k]) == 0) {
				printf("spam: match for '%s'\n", pat[k]);
				return 1;
			}
		}
		if (n < PREFIX_LEN - 1)
			n++;
		else
			c[0] = c[1];
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

	setprogname("spam-2");

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

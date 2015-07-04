/* Concatenate UTF-8 files, replacing invalid sequences with U+FFFD */

#include <stdio.h>
#include <string.h>

#include "eprintf.h"
#include "utf8.h"

enum {
	REPLACEMENT_CHAR = 0xFFFD
};

static int utf8_getc(Rune *c, FILE *fp)
{
	static char buf[BUFSIZ];
	static int i = 0;
	static size_t n = 0;

	if (i + 6 > n && i <= n && !feof(fp)) {
		/* refill the buffer */
		memmove(buf, buf + i, n - i);
		n = n - i;
		n += fread(buf + n, 1, sizeof(buf) - n, fp);
		i = 0;
	}
	if (i >= n)
		return 0;

	i += utf8_to_rune(c, buf + i);

	return 1;
}

static unsigned long utf8cat(FILE *in, FILE *out)
{
	char utf8[6];
	Rune c;
	int n;
	unsigned long count;

	while (utf8_getc(&c, in)) {
		if (c == UTF8_BADCHAR)
			c = REPLACEMENT_CHAR;
		n = rune_to_utf8(utf8, c);
		if (fwrite(utf8, n, 1, out) != 1) {
			weprintf("output error:");
			break;
		}
		count += n;
	}

	return count;
}

int main(int argc, char *argv[])
{
	int i;

	setprogname("utf8cat");
	if (argc < 2) {
		utf8cat(stdin, stdout);
	} else {
		for (i = 1; i < argc; i++) {
			FILE *fp;

			fp = fopen(argv[i], "rb");
			if (fp == NULL) {
				weprintf("can't open \"%s\":", argv[i]);
				continue;
			}
			utf8cat(fp, stdout);
			fclose(fp);
		}
	}

	return 0;
}

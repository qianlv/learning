#ifndef _UTF8_H
#define _UTF8_H

#include <stdint.h>

/* a single Unicode character */
typedef int32_t Rune;

enum {
	/* returned on UTF-8 decode error */
	UTF8_BADCHAR = -1
};

int utf8_to_rune(Rune *c, char *utf8);

int rune_to_utf8(char utf8[6], Rune c);

#endif

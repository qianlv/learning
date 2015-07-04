#include "utf8.h"

/*
0xxxxxxx (7)
110xxxxx 10xxxxxx (11)
1110xxxx 10xxxxxx 10xxxxxx (16)
11110xxx 10xxxxxx 10xxxxxx 10xxxxxx (21)
111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (26)
1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (31)
*/

/* decode utf8 to c, return the number of bytes consumed */
int utf8_to_rune(Rune *c, char *utf8)
{
	static const int N_BITS[6] = { 7, 11, 16, 21, 26, 31 };
	uint8_t prefix, mask;
	int i, n;

	/* special-case the one-byte encoding */
	if ((utf8[0] & 0x80) == 0x00) {
		*c = utf8[0];
		return 1;
	}

	prefix = 0xC0;
	mask = 0xE0;
	n = 1;
	while (mask != 0xFF) {
		if ((utf8[0] & mask) == prefix)
			goto decode;
		prefix = (prefix >> 1) | 0x80;
		mask = (mask >> 1) | 0x80;
		n++;
	}
	*c = UTF8_BADCHAR;
	return 1;

decode:
	*c = (unsigned char) (utf8[0] & ~mask) << (n * 6);
	for (i = 1; i < n + 1; i++) {
		if ((utf8[i] & 0xC0) != 0x80) {
			*c = UTF8_BADCHAR;
			return i;
		}
		*c |= (unsigned char) (utf8[i] & ~0xC0) << (n - i) * 6;
	}

	/* check for shortest encoding */
	if (*c >> N_BITS[n - 1] == 0)
		*c = UTF8_BADCHAR;

	/* check for illegal characters */
	if ((*c >= 0xD800 && *c <= 0xDFFF) || *c == 0xFFFE || *c == 0xFFFF)
		*c = UTF8_BADCHAR;

	return n + 1;
}

/* number of bytes needed to encode c */
static int rune_bytes(Rune c)
{
	if (c < 0)
		return 0;
	else if (c <= 0x7F)
		return 1;
	else if (c <= 0x7FF)
		return 2;
	else if (c <= 0xFFFF)
		return 3;
	else if (c <= 0x1FFFFF)
		return 4;
	else if (c <= 0x3FFFFFF)
		return 5;
	else if (c <= 0x7FFFFFFF)
		return 6;
	else
		return 0;
}

int rune_to_utf8(char utf8[6], Rune c)
{
	int i, n;

	if ((c & ~0x7F) == 0) {
		utf8[0] = c;
		return 1;
	}

	n = rune_bytes(c);
	if (n == 0)
		return 0;
	for (i = n - 1; i > 0; i--) {
		utf8[i] = 0x80 | (c & 0x3F);
		c >>= 6;
	}
	utf8[0] = (0xFE << (7 - n)) | c;

	return n;
}

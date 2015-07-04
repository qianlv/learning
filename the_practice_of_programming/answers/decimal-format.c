#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eprintf.h"

/* reverse: reverse bytes between s and t, inclusive */
static void reverse(char *s, char *t)
{
	char c;

	while (s < t) {
		c = *s;
		*s = *t;
		*t = c;
		s++;
		t--;
	}
}

/* growing character buffer */
struct buffer {
	char *s;	/* string buffer */
	size_t len;	/* length of string */
	size_t n;	/* size of allocation */
};

static void buffer_init(struct buffer *buf)
{
	buf->s = NULL;
	buf->len = 0;
	buf->n = 0;
}

/* append: add c to buf, growing buf if necessary */
/* frees memory and returns NULL on allocation error */
static char *append(struct buffer *buf, char c)
{
	char *p;

	while (buf->len >= buf->n) {
		if (buf->n == 0)
			buf->n = 1;
		else
			buf->n *= 2;
		p = realloc(buf->s, buf->n);
		if (p == NULL) {
			free(buf->s);
			return NULL;
		}
		buf->s = p;
	}
	buf->s[buf->len++] = c;

	return buf->s;
}

/* the returned string must be freed */
static char *decimal_format(const char *fmt, double v)
{
	double ipart, fpart;
	const char *p, *comma;
	int req_idigits, blank_idigits;
	int req_fdigits, blank_fdigits;
	int num_idigits, num_fdigits, groups;
	int point, negative, overflow;
	struct buffer digits, buf;
	int n;

	negative = signbit(v);
	v = fabs(v);
	fpart = modf(v, &ipart);

	/* handle special cases */
	if (isnan(v)) {
		return estrdup("nan");
	} else if (!isfinite(v)) {
		if (negative)
			return estrdup("-inf");
		else
			return estrdup("inf");
	}

	buffer_init(&digits);
	buffer_init(&buf);

	req_idigits = 0;
	blank_idigits = 0;
	comma = NULL;
	for (p = fmt; *p != '.' && *p != '\0'; p++) {
		if (*p == '0')
			req_idigits++;
		else if (*p == '#')
			; /* do nothing */
		else if (*p == ',')
			comma = p;
		blank_idigits++;
	}
	if (comma == NULL)
		groups = 0;
	else
		groups = p - comma - 1;

	req_fdigits = 0;
	blank_fdigits = 0;
	if (*p == '.') {
		point = 1;
		for (p++; *p != '\0'; p++) {
			if (*p == '0')
				req_fdigits++;
			else if (*p == '#')
				; /* do nothing */
			else
				break;
			blank_fdigits++;
		}
	} else {
		point = 0;
	}

	/* write the decimal digits to a buffer with no formatting */
	num_idigits = 0;
	do {
		int digit = (int) fmod(ipart, 10.0);
		ipart = floor(ipart / 10.0);
		if (append(&digits, '0' + digit) == NULL)
			return NULL;
		num_idigits++;
	} while (ipart != 0.0 || num_idigits < req_idigits);
	/* integer digits are produced in reverse order */
	reverse(digits.s, digits.s + digits.len - 1);

	num_fdigits = 0;
	for (n = 0; n < blank_fdigits; n++) {
		int digit = (int) (fpart * 10.0);
		fpart = fmod(fpart * 10.0, 1.0);
		if (append(&digits, '0' + digit) == NULL)
			return NULL;
		num_fdigits++;
	}

	/* handle a carry */
	overflow = 0;
	if (fpart >= 0.5) {
		n = digits.len - 1;
		while (n >= 0 && digits.s[n] == '0' + 9)
			digits.s[n--] = '0';
		if (n >= 0)
			digits.s[n]++;
		else
			overflow = 1;
	}
	while (num_fdigits > 0 && digits.s[num_idigits + num_fdigits - 1] == '0')
		num_fdigits--;

	/* copy integer digits (in reverse) from digits to buf */
	for (n = 0; n < num_idigits || overflow; n++) {
		if (groups > 0 && n > 0 && n % groups == 0) {
			if (append(&buf, ',') == NULL)
				return NULL;
		}
		if (n < num_idigits) {
			if (append(&buf, digits.s[num_idigits - n - 1]) == NULL)
				return NULL;
		} else if (overflow) {
			if (append(&buf, '0' + 1) == NULL)
				return NULL;
			overflow = 0;
		}
	}
	if (negative) {
		if (append(&buf, '-') == NULL)
			return NULL;
	}
	while (buf.len < blank_idigits) {
		if (append(&buf, ' ') == NULL)
			return NULL;
	}
	/* integer digits (plus commas, '-', and blanks) are in reverse order */
	reverse(buf.s, buf.s + buf.len - 1);

	if (point) {
		if (append(&buf, '.') == NULL)
			return NULL;
	}
	for (n = 0; n < blank_fdigits; n++) {
		char c;

		if (n < num_fdigits)
			c = digits.s[num_idigits + n];
		else if (n < req_fdigits)
			c = '0';
		else
			c = ' ';
		if (append(&buf, c) == NULL)
			return NULL;
	}

	free(digits.s);

	if (append(&buf, '\0') == NULL)
		return NULL;

	return buf.s;
}

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

int main(int argc, char *argv[])
{
	const char *fmt;
	char *tail, *result;
	double v;

	if (argc < 3)
		eprintf("Usage: %s <format> <number>", argv[0]);

	fmt = argv[1];
	errno = 0;
	v = strtod(argv[2], &tail);
	if (tail == argv[2] || *tail != '\0' || errno != 0)
		eprintf("Invalid number: %s", argv[2]);

	result = decimal_format(fmt, v);
	if (result == NULL)
		eprintf("Memory allocation error in decimal_format");
	printf("%s\n", result);
	free(result);

	return 0;
}

/*
	printf

	The overall strategy is to grab one printf % conversion at a time and
	call it with zero, one, two, or three arguments (can be zero for "%%",
	can be two or three with "*" width or precision).
*/

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eprintf.h"

enum {
	PRINTF_TYPE_INT,
	PRINTF_TYPE_LONG,
	PRINTF_TYPE_CHARP,
	PRINTF_TYPE_DOUBLE,
	PRINTF_TYPE_LONG_DOUBLE,
} printf_type;

enum {
	PRINTF_FLAG_ERROR = 1 << 0,
	PRINTF_FLAG_PERCENT = 1 << 1,
	PRINTF_FLAG_LEFT_ALIGN = 1 << 2,
	PRINTF_FLAG_WITH_SIGN = 1 << 3,
	PRINTF_FLAG_WITH_SPACE = 1 << 4,
	PRINTF_FLAG_PAD_ZERO = 1 << 5,
	PRINTF_FLAG_ALTERNATE = 1 << 6,
	PRINTF_FLAG_WIDTH_STAR = 1 << 7,
	PRINTF_FLAG_PRECISION_STAR = 1 << 8,
};

/* all the information contained in one printf % conversion. */
struct printf_conversion {
	unsigned int flags;
	int width;
	int precision;
	char length;
	char c;
	int type;
};

/* true if we have seen any warnings, for setting the overall return value */
static int warning_flag = 0;

/* parse_int: parse a positive integer from *s */
/* used for width and precision */
static unsigned int parse_int(const char **s)
{
	unsigned int prev, v;
	const char *p;

	v = prev = 0;
	p = *s;
	for (p = *s; isdigit(*p); p++) {
		v = v * 10 + (*p - '0');
		if (v < prev) {
			/* Overflow. */
			v = INT_MAX;
			for (p++; isdigit(*p); p++)
				;
			errno = ERANGE;
			break;
		}
		prev = v;
	}
	*s = p;

	return v;
}

/* parse_printf_conversion: parse % conversion in fmt, return rest of string */
/* sets PRINTF_FLAG_ERROR on error */
static const char *parse_printf_conversion(const char *fmt,
	struct printf_conversion *conv)
{
	const char *p;

	conv->flags = 0;
	conv->width = -1;
	conv->precision = -1;
	conv->length = '\0';
	conv->c = '\0';
	conv->type = PRINTF_TYPE_INT;

	p = fmt;
	assert(*p == '%');
	p++;
	if (*p == '\0') {
		conv->flags = PRINTF_FLAG_ERROR;
		return p;
	}
	if (*p == '%') {
		conv->flags |= PRINTF_FLAG_PERCENT;
		return p + 1;
	}
	for ( ; *p != '\0'; p++) {
		if (*p == '-')
			conv->flags |= PRINTF_FLAG_LEFT_ALIGN;
		else if (*p == '+')
			conv->flags |= PRINTF_FLAG_WITH_SIGN;
		else if (*p == ' ')
			conv->flags |= PRINTF_FLAG_WITH_SPACE;
		else if (*p == '0')
			conv->flags |= PRINTF_FLAG_PAD_ZERO;
		else if (*p == '#')
			conv->flags |= PRINTF_FLAG_ALTERNATE;
		else
			break;
	}

	if (*p == '*') {
		conv->flags |= PRINTF_FLAG_WIDTH_STAR;
		p++;
	} else if (isdigit(*p)) {
		int width;
		errno = 0;
		width = parse_int(&p);
		if (errno != 0) {
			warning_flag = 1;
			weprintf("field width too large");
			conv->flags = PRINTF_FLAG_ERROR;
			return p;
		}
		conv->width = width;
	}

	if (*p == '.') {
		p++;
		if (*p == '*') {
			conv->flags |= PRINTF_FLAG_PRECISION_STAR;
			p++;
		} else if (isdigit(*p)) {
			int precision;
			errno = 0;
			precision = parse_int(&p);
			if (errno != 0) {
				warning_flag = 1;
				weprintf("precision too large");
				conv->flags = PRINTF_FLAG_ERROR;
				return p;
			}
			conv->precision = precision;
		}
	}

	if (*p == '\0') {
		conv->flags = PRINTF_FLAG_ERROR;
		return p;
	}
	if (*p == 'h' || *p == 'l' || *p == 'L')
		conv->length = *p++;

	if (*p == '\0') {
		conv->flags = PRINTF_FLAG_ERROR;
		return p;
	}
	conv->c = *p++;
	switch (conv->c) {
	case 'd':
	case 'i':
	case 'o':
	case 'x':
	case 'X':
	case 'u':
	case 'c':
		if (conv->length == '\0' || conv->length == 'h')
			conv->type = PRINTF_TYPE_INT;
		else if (conv->length == 'l')
			conv->type = PRINTF_TYPE_LONG;
		else {
			warning_flag = 1;
			weprintf("invalid length indicator %c for %%%c",
				conv->length, conv->c);
			conv->flags = PRINTF_FLAG_ERROR;
			return p;
		}
		break;
	case 's':
		conv->type = PRINTF_TYPE_CHARP;
		break;
	case 'f':
	case 'e':
	case 'E':
	case 'g':
	case 'G':
		if (conv->length == '\0')
			conv->type = PRINTF_TYPE_DOUBLE;
		else if (conv->length == 'L')
			conv->type = PRINTF_TYPE_LONG_DOUBLE;
		else {
			warning_flag = 1;
			weprintf("invalid length indicator %c for %%%c",
				conv->length, conv->c);
			conv->flags = PRINTF_FLAG_ERROR;
			return p;
		}
		break;
	default:
		warning_flag = 1;
		weprintf("invalid format character %c", conv->c);
		conv->flags = PRINTF_FLAG_ERROR;
		return p;
		break;
	}

	return p;
}

/* render_printf_conversion: turn a conversion struct back into a % string */
/* returns number of characters written */
static int render_printf_conversion(struct printf_conversion *conv,
	char *outbuf, size_t n)
{
	/* a conversion can be as long as 9 characters, plus two base-ten ints,
	   plus \0: "%-+ 0#<int>.<int>ld\0". if we can hold two base-two ints we
	   can hold two base-ten ints. */
	char buf[10 + 2 * CHAR_BIT * sizeof(int)];
	char *p = buf;
	size_t length;

	assert((conv->flags & PRINTF_FLAG_ERROR) == 0);

	*p++ = '%';

	if ((conv->flags & PRINTF_FLAG_PERCENT) != 0) {
		*p++ = '%';
		goto finish;
	}

	if ((conv->flags & PRINTF_FLAG_LEFT_ALIGN) != 0)
		*p++ = '-';
	if ((conv->flags & PRINTF_FLAG_WITH_SIGN) != 0)
		*p++ = '+';
	if ((conv->flags & PRINTF_FLAG_WITH_SPACE) != 0)
		*p++ = ' ';
	if ((conv->flags & PRINTF_FLAG_PAD_ZERO) != 0)
		*p++ = '0';
	if ((conv->flags & PRINTF_FLAG_ALTERNATE) != 0)
		*p++ = '#';

	if ((conv->flags & PRINTF_FLAG_WIDTH_STAR) != 0)
		*p++ = '*';
	else if (conv->width >= 0)
		p += snprintf(p, n - (p - buf), "%u", conv->width);
	if ((conv->flags & PRINTF_FLAG_PRECISION_STAR) != 0)
		p += snprintf(p, n - (p - buf), ".*");
	else if (conv->precision >= 0)
		p += snprintf(p, n - (p - buf), ".%u", conv->precision);

	if (conv->length != '\0')
		*p++ = conv->length;

	*p++ = conv->c;

finish:
	*p = '\0';

	length = p - buf + 1;
	assert(length < sizeof(buf));

	if (length <= n)
		memcpy(outbuf, buf, length);

	return length;
}

static int convert_int(const char *s)
{
	char *tail;
	long v;

	errno = 0;
	v = strtol(s, &tail, 0);
	if (tail == s || *tail != '\0') {
		warning_flag = 1;
		weprintf("invalid number: %s", s);
		v = 0;
	} else if (v < INT_MIN || (errno == ERANGE && v == LONG_MIN)) {
		warning_flag = 1;
		weprintf("int constant too small: %s", s);
	} else if (v > INT_MAX || (errno == ERANGE && v == LONG_MAX)) {
		warning_flag = 1;
		weprintf("int constant too large: %s", s);
	} else if (errno != 0) {
		warning_flag = 1;
		weprintf("errno %d while parsing int: %s", s);
	}

	return (int) v;
}

static long convert_long(const char *s)
{
	char *tail;
	long v;

	errno = 0;
	v = strtol(s, &tail, 0);
	if (tail == s || *tail != '\0') {
		warning_flag = 1;
		weprintf("invalid number: %s", s);
		v = 0;
	} else if (errno == ERANGE && v == LONG_MIN) {
		warning_flag = 1;
		weprintf("long constant too small: %s", s);
	} else if (errno == ERANGE && v == LONG_MAX) {
		warning_flag = 1;
		weprintf("long constant too large: %s", s);
	} else if (errno != 0) {
		warning_flag = 1;
		weprintf("errno %d while parsing long: %s", s);
	}

	return v;
}

static const char *convert_charp(const char *s)
{
	return s;
}

static double convert_double(const char *s)
{
	char *tail;
	double v;

	errno = 0;
	v = strtod(s, &tail);
	if (tail == s || *tail != '\0') {
		warning_flag = 1;
		weprintf("invalid number: %s", s);
		v = 0;
	} else if (errno == ERANGE && v > 0.0) {
		warning_flag = 1;
		weprintf("double constant too large: %s", s);
	} else if (errno == ERANGE && v < 0.0) {
		warning_flag = 1;
		weprintf("double constant too small: %s", s);
	} else if (errno != 0) {
		warning_flag = 1;
		weprintf("errno %d while parsing double: %s", s);
	}

	return v;
}

static long double convert_long_double(const char *s)
{
	/* strtold doesn't exist before C99. */
	return (long double) convert_double(s);
}

/* call printf with one, two, or three arguments and a given conversion */
#define PRINTF_MULTI(convert) { \
	if (req_args == 1) \
		count = printf(buf, (convert)((*args)[0])); \
	else if (req_args == 2) \
		count = printf(buf, convert_int((*args)[0]), (convert)((*args)[1])); \
	else if (req_args == 3) \
		count = printf(buf, convert_int((*args)[0]), convert_int((*args)[1]), (convert)((*args)[2])); \
	else \
		eprintf("internal error: seeking %d args", req_args); \
}

/* printf_conversion_print: print one conversion's worth of args */
/* updates nargs and args to reflect the number of args consumed */
static int printf_conversion_print(struct printf_conversion *conv,
	int *nargs, char * const *args[])
{
	char buf[128];
	int req_args, count;

	if (render_printf_conversion(conv, buf, sizeof(buf)) > sizeof(buf))
		eprintf("internal error: buffer too small");

	if ((conv->flags & PRINTF_FLAG_PERCENT) != 0) {
		req_args = 0;
	} else {
		req_args = 1;
		if ((conv->flags & PRINTF_FLAG_WIDTH_STAR) != 0)
			req_args++;
		if ((conv->flags & PRINTF_FLAG_PRECISION_STAR) != 0)
			req_args++;
	}

	if (*nargs < req_args) {
		warning_flag = 1;
		weprintf("not enough args for format %s", buf);
		*args += *nargs;
		*nargs = 0;
		return 0;
	}

	if (req_args == 0)
		printf(buf);
	else if (conv->type == PRINTF_TYPE_INT)
		PRINTF_MULTI(convert_int)
	else if (conv->type == PRINTF_TYPE_LONG)
		PRINTF_MULTI(convert_long)
	else if (conv->type == PRINTF_TYPE_CHARP)
		PRINTF_MULTI(convert_charp)
	else if (conv->type == PRINTF_TYPE_DOUBLE)
		PRINTF_MULTI(convert_double)
	else if (conv->type == PRINTF_TYPE_LONG_DOUBLE)
		PRINTF_MULTI(convert_long_double)
	else
		eprintf("internal error: type %d");

	*nargs -= req_args;
	*args += req_args;

	return count;
}

static int printf_args(const char *fmt, int nargs, char * const args[])
{
	struct printf_conversion conv;
	const char *p, *q;
	int count;

	count = 0;
	p = fmt;
	while (*p != '\0') {
		q = strchr(p, '%');
		if (q == NULL)
			q = strchr(p, '\0');
		count += fwrite(p, sizeof(char), q - p, stdout);
		p = q;
		if (*p == '\0')
			break;
		q = parse_printf_conversion(p, &conv);
		if (conv.flags & PRINTF_FLAG_ERROR)
			count += fwrite(p, sizeof(char), q - p, stdout);
		else
			count += printf_conversion_print(&conv, &nargs, &args);
		p = q;
	}
	if (nargs > 0) {
		warning_flag = 1;
		weprintf("%d leftover arguments", nargs);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	const char *fmt;

	setprogname(argv[0]);
	if (argc < 2)
		eprintf("usage: printf format [arguments]");
	fmt = argv[1];

	printf_args(fmt, argc - 2, argv + 2);

	return warning_flag ? 1 : 0;
}

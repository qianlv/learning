#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "eprintf.h"
#include "pack.h"

/* read_count: read a repeat count from a format string */
/* returns 1 if no count or (ulong) -1 if overflow */
ulong read_count(char **bp)
{
	char *p;
	ulong prev, count;

	prev = count = 0;
	for (p = *bp; isdigit(*p); p++) {
		count = count * 10 + (*p - '0');
		if (count < prev) {
			/* overflow */
			count = -1;
			for (p++; isdigit(*p); p++)
				;
			break;
		}
		prev = count;
	}
	if (p == *bp)
		count = 1;
	*bp = p;

	return count;
}

/* pack: pack binary items into buf, return length */
int pack(uchar *buf, char *fmt, ...)
{
	va_list args;
	char *p;
	uchar *bp;
	ushort s;
	ulong l;
	ulong count;
	char *cp;

	bp = buf;
	va_start(args, fmt);
	for (p = fmt; *p != '\0'; p++) {
		for (count = read_count(&p); *p != '\0' && count > 0; count--) {
			switch (*p) {
			case 'c':	/* char */
				*bp++ = va_arg(args, int);
				break;
			case 's':	/* unsigned short */
			case 'S':	/* signed short */
				s = va_arg(args, int);
				*bp++ = s >> 8;
				*bp++ = s;
				break;
			case 'l':	/* unsigned long */
			case 'L':	/* signed long */
				l = va_arg(args, ulong);
				*bp++ = l >> 24;
				*bp++ = l >> 16;
				*bp++ = l >> 8;
				*bp++ = l;
				break;
			case '$':	/* string */
				l = va_arg(args, ulong);
				*bp++ = l >> 24;
				*bp++ = l >> 16;
				*bp++ = l >> 8;
				*bp++ = l;
				cp = va_arg(args, char *);
				memcpy(bp, cp, l);
				bp += l;
				break;
			default:	/* illegal type character */
				va_end(args);
				return -1;
			}
		}
	}
	va_end(args);
	return bp - buf;
}

/* pack_type1: pack format 1 packet */
int pack_type1(uchar *buf, ushort count, uchar val, ulong data)
{
	return pack(buf, "cscl", 0x01, count, val, data);
}

/* pack_type2: pack format 2 packet */
int pack_type2(uchar *buf, ushort count, ulong dw1, ulong dw2)
{
	return pack(buf, "csll", 0x01, count, dw1, dw2);
}

/* unpack: unpack packed items from buf, return length */
int unpack(uchar *buf, char *fmt, ...)
{
	va_list args;
	char *p;
	uchar *bp, *pc;
	ushort *ps;
	ulong *pl;
	ulong len, max, count;

	bp = buf;
	va_start(args, fmt);
	for (p = fmt; *p != '\0'; p++) {
		for (count = read_count(&p); *p != '\0' && count > 0; count--) {
			switch (*p) {
			case 'c':	/* char */
				pc = va_arg(args, uchar*);
				*pc = *bp++;
				break;
			case 's':	/* unsigned short */
				ps = va_arg(args, ushort*);
				*ps  = *bp++ << 8;
				*ps |= *bp++;
				break;
			case 'S':	/* signed short */
				ps = va_arg(args, ushort*);
				*ps  = ((signed char) *bp++) << 8;
				*ps |= *bp++;
				break;
			case 'l':	/* unsigned long */
				pl = va_arg(args, ulong*);
				*pl  = *bp++ << 24;
				*pl |= *bp++ << 16;
				*pl |= *bp++ << 8;
				*pl |= *bp++;
				break;
			case 'L':	/* signed long */
				pl = va_arg(args, ulong*);
				*pl  = ((signed char) *bp++) << 24;
				*pl |= *bp++ << 16;
				*pl |= *bp++ << 8;
				*pl |= *bp++;
				break;
			case '$':	/* string */
				max = va_arg(args, ulong);
				pc = va_arg(args, uchar*);
				len  = ((signed char) *bp++) << 24;
				len |= *bp++ << 16;
				len |= *bp++ << 8;
				len |= *bp++;
				memcpy(pc, bp, len < max ? len : max);
				bp += len;
				break;
			default:	/* illegal type character */
				va_end(args);
				return -1;
			}
		}
	}
	va_end(args);
	return bp - buf;
}

/* process_type1: process type 1 packet */
int process_type1(ushort count, uchar val, ulong data)
{
	return 0;
}

/* process_type2: process type 2 packet */
int process_type2(ushort count, ulong dw1, ulong dw2)
{
	return 0;
}

/* unpack_type0: unpack and process type 0 packet */
int unpack_type0(int n, uchar *buf)
{
	assert(0);
}

/* unpack_type1: unpack and process type 1 packet */
int unpack_type1(int n, uchar *buf)
{
	uchar c, val;
	ushort count;
	ulong data;

	if (unpack(buf, "cscl", &c, &count, &val, &data) != n)
		return -1;
	assert(c == 0x01);
	return process_type1(count, val, data);
}

/* unpack_type2: unpack and process type 2 packet */
int unpack_type2(int n, uchar *buf)
{
	uchar c;
	ushort count;
	ulong dw1, dw2;

	if (unpack(buf, "csll", &c, &count, &dw1, &dw2) != n)
		return -1;
	assert(c == 0x02);
	return process_type2(count, dw1, dw2);
}

/* readpacket: read packet from network */
int readpacket(int network, uchar *buf, size_t len)
{
	return 0;
}

int (*unpackfn[])(int, uchar *) = {
	unpack_type0,
	unpack_type1,
	unpack_type2,
};

/* receive: read packets from network, process them */
void receive(int network)
{
	uchar type, buf[BUFSIZ];
	int n;

	while ((n = readpacket(network, buf, BUFSIZ)) > 0) {
		type = buf[0];
		if (type >= NELEMS(unpackfn))
			eprintf("bad packet type 0x%x", type);
		if ((*unpackfn[type])(n, buf) < 0)
			eprintf("protocol error, type %x length %d",
				type, n);
	}
}

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "eprintf.h"
#include "pack.h"

/* pack: pack binary items into buf, return length */
int pack(uchar *buf, char *fmt, ...)
{
	va_list args;
	char *p;
	uchar *bp;
	ushort s;
	ulong l;

	bp = buf;
	va_start(args, fmt);
	for (p = fmt; *p != '\0'; p++) {
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
		default:	/* illegal type character */
			va_end(args);
			return -1;
		}
	}
	va_end(args);
	return bp - buf;
}

/* unpack: unpack packed items from buf, return length */
int unpack(uchar *buf, char *fmt, ...)
{
	va_list args;
	char *p;
	uchar *bp, *pc;
	ushort *ps;
	ulong *pl;

	bp = buf;
	va_start(args, fmt);
	for (p = fmt; *p != '\0'; p++) {
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
		default:	/* illegal type character */
			va_end(args);
			return -1;
		}
	}
	va_end(args);
	return bp - buf;
}

class packet {
public:
	static const int type;

	virtual int unpack(int n, uchar *buf) = 0;
	virtual int pack(uchar *buf) = 0;
	virtual int process();
};

class packet_type1 : public packet {
private:
	uchar val;
	ushort count;
	ulong data;

public:
	static const int type = 1;

	packet_type1() : val(0), count(0), data(0)
	{
	}

	virtual int unpack(int n, uchar *buf)
	{
		uchar c;

		if (::unpack(buf, "cscl", &c, &count, &val, &data) != n)
			return -1;
		assert(c == 0x01);
		return n;
	}

	virtual int pack(uchar *buf)
	{
		return ::pack(buf, "cscl", 0x01, count, val, data);
	}

	virtual int process()
	{
		return 0;
	}
};

class packet_type2 : public packet {
private:
	ushort count;
	ulong dw1, dw2;

public:
	static const int type = 2;

	packet_type2() : count(0), dw1(0), dw2(0)
	{
	}

	virtual int unpack(int n, uchar *buf)
	{
		uchar c;

		if (::unpack(buf, "csll", &c, &count, &dw1, &dw2) != n)
			return -1;
		assert(c == 0x02);
		return n;
	}

	virtual int pack(uchar *buf)
	{
		return ::pack(buf, "csll", 0x01, count, dw1, dw2);
	}

	virtual int process()
	{
		return 0;
	}
};

/* readpacket: read packet from network */
int readpacket(int network, uchar *buf, size_t len)
{
	return 0;
}

/* getpacket: read packet from network and return packet object */
packet *getpacket(int network)
{
	uchar type, buf[BUFSIZ];
	packet *p;
	int n;

	n = readpacket(network, buf, BUFSIZ);
	if (n == 0)
		return NULL;
	type = buf[0];
	switch (type) {
	default:
		eprintf("bad packet type 0x%x", type);
		break;
	case 1:
		p = new packet_type1();
		break;
	case 2:
		p = new packet_type2();
		break;
	}
	if (p->unpack(n, buf) < 0)
		eprintf("protocol error, type %x length %d", type, n);

	return p;
}

/* receive: read packets from network, process them */
void receive(int network)
{
	packet *p;

	while ((p = getpacket(network)) != NULL) {
		if (p->process() < 0)
			eprintf("protocol error, type %x", p->type);
		delete p;
	}
}

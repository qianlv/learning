#ifndef _PACK_H
#define _PACK_H

typedef unsigned char	uchar;
typedef unsigned short	ushort;
typedef unsigned long	ulong;

int pack(uchar *buf, char *fmt, ...);

int unpack(uchar *buf, char *fmt, ...);

void receive(int network);

#endif

/*
This is a checking implementation of malloc and free. Each free and
in-use block is bracketed by a header and tailer (identical within a
block). The header and tailer contain magic values that identify whether
a block is free or in-use; if a value isn't one of these two it is an
error. The integrity of the storage is checked before and after every
malloc and free. Any inconsistencies will cause an error to be printed
and the program to halt.

References to free and in-use blocks are kept in circular linked lists,
each initialized with a single empty block.

The allocator is based on the one from section 8.7 of the book The C
Programming Language.
*/

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* magic values stored in headers and tailers to detect overwriting
   or the wrong block type in a list */
static const int FREE_MAGIC = 0x01234567;
static const int INUSE_MAGIC = 0xFEDCBA98;

typedef long Align;	/* For alignment of memory blocks. */

union header {
	struct {
		int magic_1;
		union header *ptr;
		size_t size;
		int magic_2;
	} s;
	Align x;	/* Force alignment of blocks. */
};

typedef union header Header;

/* Empty lists to get started. Initial blocks are arrays of size 2 for the
   header, tailer, and nothing in between. */
static Header freebase[2];
static Header *freep = NULL;
static int freecount = 0;
static Header inusebase[2];
static Header *inusep = NULL;
static int inusecount = 0;

static void assert(int cond, char *fmt, ...)
{
	va_list args;

	if (cond)
		return;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	fprintf(stderr, "\n");

	abort();
}

static Header *get_tail(Header *head)
{
	return head + head->s.size - 1;
}

static void free_intact(Header *head)
{
	Header *tail;
	
	tail = get_tail(head);
	assert(head->s.magic_1 == FREE_MAGIC && head->s.magic_2 == FREE_MAGIC,
		"free malloc header scrambled (head %p, tail %p, user pointer %p)",
			head, tail, head + 1);
	assert(tail->s.magic_1 == FREE_MAGIC && tail->s.magic_2 == FREE_MAGIC,
		"free malloc tailer scrambled (head %p, tail %p, user pointer %p)",
			head, tail, head + 1);
}

static void inuse_intact(Header *head)
{
	Header *tail;

	tail = get_tail(head);
	assert(head->s.magic_1 == INUSE_MAGIC && head->s.magic_2 == INUSE_MAGIC,
		"in-use malloc header scrambled (head %p, tail %p, user pointer %p)",
			head, tail, head + 1);
	assert(tail->s.magic_1 == INUSE_MAGIC && tail->s.magic_2 == INUSE_MAGIC,
		"in-use malloc tailer scrambled (head %p, tail %p, user pointer %p)",
			head, tail, head + 1);
}

static void free_init(Header *head)
{
	head->s.magic_1 = FREE_MAGIC;
	head->s.ptr = NULL;
	head->s.size = 0;
	head->s.magic_2 = FREE_MAGIC;
}

static void inuse_init(Header *head)
{
	head->s.magic_1 = INUSE_MAGIC;
	head->s.ptr = NULL;
	head->s.size = 0;
	head->s.magic_2 = INUSE_MAGIC;
}

/* check:  check the integrity of the storage system, and halt if
   anything is wrong */
static void check(void)
{
	Header *p;
	int count;

	count = 0;
	p = freep;
	do {
		count++;
		free_intact(p);
		p = p->s.ptr;
	} while (p != freep);
	assert(count == freecount,
		"free block count incorrect: should be %d, but are %d", freecount, count);

	count = 0;
	p = inusep;
	do {
		count++;
		inuse_intact(p);
		p = p->s.ptr;
	} while (p != inusep);
	assert(count == inusecount,
		"in-use block count incorrect: should be %d, but are %d", freecount, count);
}

/* primitive_free:  add a block to the free list (does not check
   integrity or affect the in-use list. Note that this function takes a
   header address, not a user pointer address. */
static void primitive_free(Header *bp)
{
	Header *p;

	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;	/* freed block at start or end of arena */

	freecount++;
	if (bp + bp->s.size == p->s.ptr) {	/* join to upper nbr */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
		freecount--;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {	/* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
		freecount--;
	} else
		p->s.ptr = bp;
	*get_tail(p) = *p;
	freep = p;
}

#define NALLOC 1024	/* minimum #units to request */

/* morecore:  ask system for more memory */
static Header *morecore(size_t nu)
{
	char *cp, *sbrk(int);
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)	/* no space at all */
		return NULL;
	up = (Header *) cp;
	free_init(up);
	up->s.size = nu;
	primitive_free(up);
	return freep;
}

/* init:  set up initial empty block lists */
static void init(void)
{
	free_init(freebase);
	freebase->s.ptr = freebase;
	freebase->s.size = 2;
	*get_tail(freebase) = *freebase;
	freep = freebase;
	freecount = 1;

	inuse_init(inusebase);
	inusebase->s.ptr = inusebase;
	inusebase->s.size = 2;
	*get_tail(inusebase) = *inusebase;
	inusep = inusebase;
	inusecount = 1;
}

/* malloc:  special-purpose checking storage allocator */
void *malloc(size_t size)
{
	Header *p, *prevp;
	size_t nunits;

	nunits = (size + 2 * sizeof(Header) - 1) / sizeof(Header) + 1;
	if (freep == NULL)	/* no free lists yet */
		init();

	check();

	prevp = freep;
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {	/* big enough */
			if (p->s.size == nunits) {	/* exactly */
				/* unlink from free list */
				prevp->s.ptr = p->s.ptr;
				freecount--;
				/* link to in-use list */
				inuse_init(p);
				p->s.size = nunits;
				p->s.ptr = inusep->s.ptr;
				inusep->s.ptr = p;
				*get_tail(p) = *p;
			} else {	/* allocate tail end */
				/* reduce size of free block */
				p->s.size -= nunits;
				*get_tail(p) = *p;

				/* link to in-use list */
				p += p->s.size;
				inuse_init(p);
				p->s.size = nunits;
				p->s.ptr = inusep->s.ptr;
				inusep->s.ptr = p;
				*get_tail(p) = *p;
			}
			inusecount++;
			freep = prevp;
			check();
			return (void *)(p + 1);
		}
		if (p == freep)	{	/* wrapped around free list */
			errno = 0;
			assert((p = morecore(nunits)) != NULL,
				"morecore(%u) failed: %s", nunits, strerror(errno));
		}
	}
}

/* free:  add block ap to free list and remove from in-use list */
void free(void *ap)
{
	Header *bp, *p;

	if (ap == NULL)
		return;

	if (freep == NULL)	/* no free lists yet */
		init();

	bp = (Header *) ap - 1;
	check();
	inuse_intact(bp);
	/* unlink from in-use list */
	for (p = inusep; p->s.ptr != bp; p = p->s.ptr)
		;
	p->s.ptr = bp->s.ptr;
	primitive_free(bp);
	inusecount--;
	check();
}

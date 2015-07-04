#include <stdio.h>
#include <string.h>

#include "timer.h"

void *slow_memset(void *block, int c, size_t n)
{
	unsigned char *p = block;
	int i;

	for (i = 0; i < n; i++)
		p[i] = c;

	return p;
}

/* the type used for block memset */
typedef unsigned int memset_t;
/* bit mask for doing a quick mod with sizeof(memset_t), assumed to be
   a power of two */
#define MEMSET_ALIGN_MASK ((sizeof(memset_t) - 1))

void *fast_memset(void *block, int c, size_t n)
{
	unsigned char *pc = block;
	memset_t *pm, m;

	while (n > 0 && ((unsigned long) pc & MEMSET_ALIGN_MASK) != 0) {
		*pc++ = c;
		n--;
	}
	if (n >= sizeof(memset_t)) {
		/* block copy where the byte copy left off */
		pm = (memset_t *) pc;
		/* fill the block element */
		pc = (unsigned char *) &m;
		while (pc - (unsigned char *) &m < sizeof(memset_t))
			*pc++ = c;
		/* block copy */
		while (n >= sizeof(memset_t)) {
			*pm++ = m;
			n -= sizeof(memset_t);
		}
		pc = (unsigned char *) pm;
	}
	while (n > 0) {
		*pc++ = c;
		n--;
	}

	return block;
}
#define MAX_SIZE (1024 * 1024 * 4)
#define MAX_OFFSET (sizeof(memset_t))
#define ARRAY_SIZE (MAX_SIZE + MAX_OFFSET)

unsigned char array[ARRAY_SIZE];

void run_memsets(size_t size)
{
	struct {
		const char *name;
		void *(*fn)(void *, int, size_t);
	} memsets[] = {
		{ "library memset", memset },
		{ "byte-at-a-time memset", slow_memset },
		{ "word-at-a-time memset", fast_memset },
	};
	int i, offset;

	printf("size %u\n", (unsigned int) size);
	printf("%22s ", "offset");
	for (offset = 0; offset < MAX_OFFSET; offset++)
		printf(" %8d", offset);
	printf("\n");
	for (i = 0; i < sizeof(memsets) / sizeof(memsets[0]); i++) {
		void *(*fn)(void *, int, size_t) = memsets[i].fn;
		printf("%22s:", memsets[i].name);

		for (offset = 0; offset < MAX_OFFSET; offset++) {
			timer_start();
			fn(array + offset, 'C', size);
			printf(" %8g", timer_elapsed());
		}
		printf("\n");
	}
}

int main(void)
{
	int a, b, t;

	/* Fibonacci numbers F_29 and F_30. */
	a = 514229;
	b = 832040;
	while (b <= ARRAY_SIZE) {
		run_memsets(b);
		t = a + b;
		a = b;
		b = t;
	}

	return 0;
}

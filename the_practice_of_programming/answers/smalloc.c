#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	SMALL_SIZE = 12,	/* size of a "small string", including \0 */
	BLOCK_SIZE = 128	/* allocate this many small strings at once */
};

struct smalloc_s {
	struct smalloc_s *next;
	char *p;	/* points to s or to a malloc allocation */
	char s[SMALL_SIZE];
};

/* smalloc_block_new: create and return a new block of smalloc_s */
/* these blocks are never freed */
static struct smalloc_s *smalloc_block_new(void)
{
	struct smalloc_s *p;
	int i;

	p = malloc(sizeof(*p) * BLOCK_SIZE);
	if (p == NULL)
		return NULL;
	/* make a linked list of the new free strings */
	for (i = 0; i < BLOCK_SIZE - 1; i++) {
		p[i].next = &p[i + 1];
		p[i].p = NULL;
	}
	p[i].next = NULL;
	p[i].p = NULL;

	return p;
}

static struct smalloc_s *freep = NULL;
static struct smalloc_s *inusep = NULL;

/* smalloc: string allocator, efficient for short strings */
/* len is string length, not including null terminator */
char *smalloc(size_t len)
{
	struct smalloc_s *np;

	if (freep == NULL) {
		/* no free strings */
		freep = smalloc_block_new();
		if (freep == NULL)
			return NULL;
	}
	np = freep;
	if (len < SMALL_SIZE) {
		/* local allocation, point to the local array */
		np->p = np->s;
	} else {
		/* malloc allocation */
		np->p = malloc(len + 1);
		if (np->p == NULL)
			return NULL;
	}

	/* add to in-use list, remove from free list */
	freep = np->next;
	np->next = inusep;
	inusep = np;

	return np->p;
}

/* sfree: free a smalloc-allocated string */
void sfree(char *s)
{
	struct smalloc_s *sp, *prev;

	/* find the smalloc_s containing this string */
	for (prev = NULL, sp = inusep; sp != NULL; prev = sp, sp = sp->next) {
		if (sp->p == s)
			break;
	}
	/* sp == NULL means the string was not allocated by smalloc */
	assert(sp != NULL);
	/* free if a malloc allocation */
	if (sp->p != sp->s)
		free(sp->p);
	sp->p = NULL;

	/* ulink from in-use list, add to free list */
	if (prev == NULL)
		inusep = sp->next;
	else
		prev->next = sp->next;
	sp->next = freep;
	freep = sp;
}

int main(void)
{
	const size_t ARRAY_SIZE = BLOCK_SIZE * 2;
	char *small, *large;
	char *strings[ARRAY_SIZE];
	int i;

	small = smalloc(3);
	large = smalloc(100);
	strcpy(small, "cat");
	strcpy(large, "honorificabilitudinitatibus");
	printf("small %p \"%s\"\n", small, small);
	printf("large %p \"%s\"\n", large, large);

	sfree(small);
	small = smalloc(3);
	strcpy(small, "dog");
	printf("small %p \"%s\"\n", small, small);
	printf("large %p \"%s\"\n", large, large);
	sfree(large);

	/* triggers a malloc allocation because of terminator */
	large = smalloc(SMALL_SIZE);
	large[0] = '\0';
	printf("small %p \"%s\"\n", small, small);
	printf("large %p \"%s\"\n", large, large);

	/* force allocation of several blocks */
	for (i = 0; i < ARRAY_SIZE; i++)
		strings[i] = smalloc(0);
	/* free the strings in a different order */
	i = 0;
	do {
		sfree(strings[i]);
		/* prime number increment visits every element */
		i = (i + 13) % ARRAY_SIZE;
	} while (i != 0);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eprintf.h"

typedef struct Nameval Nameval;
struct Nameval {
	char *name;
	int value;
	Nameval *next;	/* in list */
};

/* newitem: create new item from name and value */
Nameval *newitem(char *name, int value)
{
	Nameval *newp;

	newp = (Nameval *) emalloc(sizeof(Nameval));
	newp->name = name;
	newp->value = value;
	newp->next = NULL;
	return newp;
}

/* addfront: add newp to front of listp */
Nameval *addfront(Nameval *listp, Nameval *newp)
{
	newp->next = listp;
	return newp;
}

/* addend: add newp to end of listp */
Nameval *addend(Nameval *listp, Nameval *newp)
{
	Nameval *p;

	if (listp == NULL)
		return newp;
	for (p = listp; p->next != NULL; p = p->next)
		;
	p->next = newp;
	return listp;
}

/* lookup: sequential search for name in listp */
Nameval *lookup(Nameval *listp, char *name)
{
	for ( ; listp != NULL; listp = listp->next)
		if (strcmp(name, listp->name) == 0)
			return listp;
	return NULL;	/* no match */
}

/* apply: execute fn for each element of listp */
void apply(Nameval *listp,
	void (*fn)(Nameval*, void*), void *arg)
{
	for ( ; listp != NULL; listp = listp->next)
		(*fn)(listp, arg);	/* call the function */
}

/* printnv: print name and value using format in arg */
void printnv(Nameval *p, void *arg)
{
	char *fmt;

	fmt = (char *) arg;
	printf(fmt, p->name, p->value);
}

/* inccounter: increment counter *arg */
void inccounter(Nameval *p, void *arg)
{
	int *ip;

	/* p is unused */
	ip = (int *) arg;
	(*ip)++;
}

/* freeall: free all elements of listp */
void freeall(Nameval *listp)
{
	Nameval *next;

	for ( ; listp != NULL; listp = next) {
		next = listp->next;
		/* assumes name is freed elsewhere */
		free(listp);
	}
}

/* delitem: delete first "name" from listp */
Nameval *delitem(Nameval *listp, char *name)
{
	Nameval *p, *prev;

	prev = NULL;
	for (p = listp; p != NULL; p = p->next) {
		if (strcmp(name, p->name) == 0) {
			if (prev == NULL)
				listp = p->next;
			else
				prev->next = p->next;
			free(p);
			return listp;
		}
		prev = p;
	}
	eprintf("delitem: %s not in list", name);
	return NULL;	/* can't get here */
}	

void print(const Nameval *listp)
{
	const Nameval *p;

	printf("{");
	for (p = listp; p != NULL; p = p->next) {
		if (p == listp)
			printf(" ");
		else
			printf(", ");
		printf("%s:%d", p->name, p->value);
	}
	printf(" }\n");
}

int count(const Nameval *listp)
{
	int n;

	n = 0;
	apply((Nameval *) listp, inccounter, &n);

	return n;
}

Nameval *referencelist(void)
{
	Nameval *listp = NULL;

	listp = addfront(listp, newitem("AElig",  0x00c6));
	listp = addfront(listp, newitem("Aacute", 0x00c1));
	listp = addfront(listp, newitem("Acirc",  0x00c2));
	listp = addfront(listp, newitem("zeta",   0x03b6));

	return listp;
}

/* copy: copy an original list */
Nameval *copy(const Nameval *original)
{
	Nameval *listp, *p, *prev;

	prev = NULL;
	for ( ; original != NULL; original = original->next) {
		p = newitem(original->name, original->value);
		if (prev == NULL)
			listp = p;
		else
			prev->next = p;
		prev = p;
	}

	return listp;
}

/* merge: append listb to lista */
Nameval *merge(Nameval *lista, Nameval *listb)
{
	Nameval *p;

	if (lista == NULL)
		return listb;

	for (p = lista; p->next != NULL; p = p->next)
		;
	p->next = listb;

	return lista;
}

/* split: split a list before the first node whose name is name,
   returning one list and storing the other in other. */
Nameval *split(Nameval *listp, const char *name, Nameval **other)
{
	Nameval *p, *prev;

	prev = NULL;
	for (p = listp; p != NULL; p = p->next) {
		if (strcmp(p->name, name) == 0) {
			*other = p;
			if (prev == NULL)
				listp = NULL;
			else
				prev->next = NULL;
			return listp;
		}
		prev = p;
	}
	*other = NULL;

	return listp;
}

/* insert_before: insert newp before the given item */
Nameval *insert_before(Nameval *listp, Nameval *item, Nameval *newp)
{
	Nameval *p, *prev;

	prev = NULL;
	for (p = listp; p != NULL; p = p->next) {
		if (p == item) {
			p = addfront(item, newp);
			if (prev == NULL)
				listp = p;
			else
				prev->next = p;
			return listp;
		}
		prev = p;
	}
	eprintf("insert_before: %s:%d not in list", item->name, item->value);
	return NULL;	/* can't get here */
}

/* insert_after: insert newp after the given item, assuming item is in list */
Nameval *insert_after(Nameval *listp, Nameval *item, Nameval *newp)
{
	item->next = addfront(item->next, newp);

	return listp;
}

/* reverse_iterative: reverse a list in place */
Nameval *reverse_iterative(Nameval *listp)
{
	Nameval *prev, *next;

	prev = NULL;
	for ( ; listp != NULL; listp = next) {
		next = listp->next;
		listp->next = prev;
		prev = listp;
	}

	return prev;
}

Nameval *reverse_recursive_helper(Nameval *listp, Nameval *partial)
{
	Nameval *next;

	if (listp == NULL)
		return partial;
	next = listp->next;

	return reverse_recursive_helper(next, addfront(partial, listp));
}

/* reverse_recursive: reverse a list in place */
Nameval *reverse_recursive(Nameval *listp)
{
	return reverse_recursive_helper(listp, NULL);
}

/* lists_equal: return true if lista and listb have the same contents */
int lists_equal(const Nameval *lista, const Nameval *listb)
{
	while (lista != NULL && listb != NULL) {
		if (strcmp(lista->name, listb->name) != 0
		    || lista->value != listb->value) {
			return 0;
		}
		lista = lista->next;
		listb = listb->next;
	}

	return lista == NULL && listb == NULL;
}

int lists_reversed_helper(const Nameval **p, const Nameval *list)
{
	/* find the end of the second list */
	if (list == NULL)
		return 1;
	if (lists_reversed_helper(p, list->next)) {
		/* on the way back up, compare with elements of the
		   first list, advancing the pointer */
		if (*p != NULL
		    && strcmp((*p)->name, list->name) == 0
		    && (*p)->value == list->value) {
			*p = (*p)->next;
			return 1;
		}
	}

	return 0;
}

/* lists_reversed: return true if lista is the reverse of listb */
int lists_reversed(const Nameval *lista, const Nameval *listb)
{
	const Nameval **p;

	p = &lista;

	return lists_reversed_helper(p, listb) && *p == NULL;
}

int test_copy(void)
{
	Nameval *listp, *c;
	int equal;

	listp = referencelist();
	c = copy(listp);
	equal = lists_equal(listp, c);
	freeall(listp);
	freeall(c);

	return equal;
}

int test_merge(void)
{
	Nameval *lista, *listb, *m;
	int total;
	int success;

	success = 1;
	lista = referencelist();
	listb = referencelist();
	total = count(lista) + count(listb);
	m = merge(copy(lista), copy(listb));
	if (count(m) != total)
		success = 0;
	freeall(lista);
	freeall(listb);
	freeall(m);

	return success;
}

int test_split(void)
{
	Nameval *ref, *listp, *other;
	int success;

	success = 1;
	ref = referencelist();
	listp = split(ref, ref->name, &other);
	if (listp != NULL || other != ref)
		success = 0;
	freeall(listp);
	freeall(other);
	if (!success)
		return 0;

	ref = referencelist();
	listp = split(ref, "Acirc", &other);
	if (listp == NULL || strcmp(listp->name, ref->name) != 0
	    || other == NULL || strcmp(other->name, "Acirc") != 0) {
		success = 0;
	}
	freeall(listp);
	freeall(other);
	if (!success)
		return 0;

	ref = referencelist();
	listp = split(ref, "nonexistent", &other);
	if (listp != ref || other != NULL)
		success = 0;
	freeall(listp);
	freeall(other);
	if (!success)
		return 0;

	return success;
}

int test_insert_before(void)
{
	Nameval *listp;
	int size;

	listp = referencelist();
	size = count(listp);
	listp = insert_before(listp, listp, newitem("smiley", 0x263A));
	if (count(listp) != size + 1 || strcmp(listp->name, "smiley") != 0) {
		freeall(listp);
		return 0;
	}
	listp = insert_before(listp, lookup(listp, "zeta"), newitem("nul", 0x0000));
	if (count(listp) != size + 2 || lookup(listp, "nul") == NULL) {
		freeall(listp);
		return 0;
	}
	freeall(listp);

	return 1;
}

int test_insert_after(void)
{
	Nameval *listp;
	int size;

	listp = referencelist();
	size = count(listp);
	listp = insert_after(listp, listp, newitem("smiley", 0x263A));
	if (count(listp) != size + 1 || lookup(listp, "smiley") == NULL) {
		freeall(listp);
		return 0;
	}
	freeall(listp);

	return 1;
}

int test_reverse_iterative(void)
{
	Nameval *listp, *rev;
	int reversed;

	listp = referencelist();
	rev = copy(listp);
	rev = reverse_iterative(rev);
	reversed = lists_reversed(listp, rev);
	freeall(listp);
	freeall(rev);

	return reversed;
}

int test_reverse_recursive(void)
{
	Nameval *listp, *rev;
	int reversed;

	listp = referencelist();
	rev = copy(listp);
	rev = reverse_recursive(rev);
	reversed = lists_reversed(listp, rev);
	freeall(listp);
	freeall(rev);

	return reversed;
}

int main(int argc, char *argv[])
{
	printf("test_copy: %s\n", test_copy() ? "pass" : "fail");
	printf("test_merge: %s\n", test_merge() ? "pass" : "fail");
	printf("test_split: %s\n", test_split() ? "pass" : "fail");
	printf("test_insert_before: %s\n", test_insert_before() ? "pass" : "fail");
	printf("test_insert_after: %s\n", test_insert_after() ? "pass" : "fail");
	printf("test_reverse_iterative: %s\n", test_reverse_iterative() ? "pass" : "fail");
	printf("test_reverse_recursive: %s\n", test_reverse_recursive() ? "pass" : "fail");

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "eprintf.h"

typedef struct Nameval Nameval;
struct Nameval {
	char *name;
	int value;
	Nameval *left;	/* lesser */
	Nameval *right;	/* greater */
};

/* newitem: create new item from name and value */
Nameval *newitem(char *name, int value)
{
	Nameval *newp;

	newp = (Nameval *) emalloc(sizeof(Nameval));
	newp->name = name;
	newp->value = value;
	newp->left = NULL;
	newp->right = NULL;
	return newp;
}

/* insert: insert newp in treep, return treep */
Nameval *insert(Nameval *treep, Nameval *newp)
{
	int cmp;

	if (treep == NULL)
		return newp;
	cmp = strcmp(newp->name, treep->name);
	if (cmp == 0)
		weprintf("insert: duplicate entry %s ignored",
			newp->name);
	else if (cmp < 0)
		treep->left = insert(treep->left, newp);
	else
		treep->right = insert(treep->right, newp);
	return treep;
}

/* lookup: look up name in tree treep */
Nameval *lookup(Nameval *treep, char *name)
{
	int cmp;

	if (treep == NULL)
		return NULL;
	cmp = strcmp(name, treep->name);
	if (cmp == 0)
		return treep;
	else if (cmp < 0)
		return lookup(treep->left, name);
	else
		return lookup(treep->right, name);
}

/* nrlookup: non-recursively look up name in tree treep */
Nameval *nrlookup(Nameval *treep, char *name)
{
	int cmp;

	while (treep != NULL) {
		cmp = strcmp(name, treep->name);
		if (cmp == 0)
			return treep;
		else if (cmp < 0)
			treep = treep->left;
		else
			treep = treep->right;
	}
	return NULL;
}

/* applyinorder: inorder application of fn to treep */
void applyinorder(Nameval *treep,
	void (*fn)(Nameval*, void*), void *arg)
{
	if (treep == NULL)
		return;
	applyinorder(treep->left, fn, arg);
	(*fn)(treep, arg);
	applyinorder(treep->right, fn, arg);
}

/* freeall: free the memory used by each node in treep */
void freeall(Nameval *treep)
{
	if (treep == NULL)
		return;
	freeall(treep->left);
	freeall(treep->right);
	free(treep);
}

int test_insert(void)
{
	Nameval *treep;
	Nameval *a, *b;

	treep = NULL;
	a = newitem("smiley", 0x263a);
	treep = insert(treep, a);
	if (treep != a) {
		free(a);
		return 0;
	}
	b = newitem("zeta", 0x03b6);
	treep = insert(treep, b);
	if (treep != a || treep->left != NULL || treep->right != b) {
		free(a);
		free(b);
		return 0;
	}
	freeall(treep);

	return 1;
}

/* int_to_string: return a string representation of n in a dynamically allocated
   buffer. */
static char *int_to_string(int n)
{
	size_t size;
	char *buf;

	size = snprintf(NULL, 0, "%d", n);
	buf = emalloc(size + 1);
	snprintf(buf, 0, "%d", n);

	return buf;
}

/* build_tree: build a dummy balanced tree for benchmark purposes */
static Nameval *build_tree(int low, int high)
{
	Nameval *newp;
	int mid;

	if (low >= high)
		return NULL;
	mid = low + (high - low) / 2;
	newp = newitem(int_to_string(mid), mid);
	newp->left = build_tree(low, mid);
	newp->right = build_tree(mid + 1, high);

	return newp;
}

static void free_name(Nameval *node, void *arg)
{
	/* arg is unused */
	free(node->name);
}

#define TREE_SIZE 50000

int main(int argc, char *argv[])
{
	char *nums[TREE_SIZE];
	Nameval *treep;
	clock_t start, end;
	int i;

	printf("test_insert: %s\n", test_insert() ? "pass" : "fail");

	/* precalculate the names used for lookup */
	for (i = 0; i < TREE_SIZE; i++)
		nums[i] = int_to_string(i);

	/* build a reference tree */
	start = clock();
	treep = build_tree(0, TREE_SIZE);
	end = clock();
	printf("build tree: %.4f s\n", (double) (end - start) / CLOCKS_PER_SEC);

	start = clock();
	for (i = 0; i < TREE_SIZE; i++)
		lookup(treep, nums[i]);
	end = clock();
	printf("lookup: %.4f s\n", (double) (end - start) / CLOCKS_PER_SEC);

	start = clock();
	for (i = 0; i < TREE_SIZE; i++)
		nrlookup(treep, nums[i]);
	end = clock();
	printf("nrlookup: %.4f s\n", (double) (end - start) / CLOCKS_PER_SEC);

	for (i = 0; i < TREE_SIZE; i++)
		free(nums[i]);

	applyinorder(treep, free_name, NULL);

	return 0;
}

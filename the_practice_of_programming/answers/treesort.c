#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "eprintf.h"

struct tree_node {
	int value;
	struct tree_node *left;
	struct tree_node *right;
};

static struct tree_node *newnode(int value)
{
	struct tree_node *newp;

	newp = emalloc(sizeof(struct tree_node));
	newp->value = value;
	newp->left = NULL;
	newp->right = NULL;

	return newp;
}

static struct tree_node *insert(struct tree_node *treep,
	struct tree_node *newp)
{
	if (treep == NULL)
		return newp;
	if (newp->value < treep->value)
		treep->left = insert(treep->left, newp);
	else
		treep->right = insert(treep->right, newp);

	return treep;
}

static void freeall(struct tree_node *treep)
{
	if (treep == NULL)
		return;
	freeall(treep->left);
	freeall(treep->right);
	free(treep);
}

static void enumerate(const struct tree_node *treep, int **v)
{
	if (treep == NULL)
		return;
	enumerate(treep->left, v);
	**v = treep->value;
	(*v)++;
	enumerate(treep->right, v);
}

/* treesort: sort v[0]..v[n-1] into increasing order */
void treesort(int v[], unsigned int n)
{
	struct tree_node *treep;
	unsigned int i;

	treep = NULL;
	for (i = 0; i < n; i++)
		treep = insert(treep, newnode(v[i]));
	enumerate(treep, &v);
	freeall(treep);
}

/* swap:  interchange v[i] and v[j] */
static void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* quicksort: sort v[0]..v[n-1] into increasing order */
void quicksort(int v[], unsigned int n)
{
	int i, last;

	if (n <= 1) /* nothing to do */
		return;
	swap(v, 0, rand() % n);	/* move pivot elem to v[0] */
	last = 0;
	for (i = 1; i < n; i++)	/* partition */
		if (v[i] < v[0])
			swap(v, ++last, i);
	swap(v, 0, last);	/* restore pivot */
	quicksort(v, last);	/* recursively sort */
	quicksort(v+last+1, n-last-1);	/* each part */
}

static int cmp_int(const void *a, const void *b)
{
	if (*((int *) a) < *((int *) b))
		return -1;
	else if (*((int *) a) == *((int *) b))
		return 0;
	else
		return 1;
}

/* library_quicksort: sort v[0]..v[n-1] into increasing order */
void library_quicksort(int v[], unsigned int n)
{
	qsort(v, n, sizeof(v[0]), cmp_int);
}

static void fill_random(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		v[i] = rand();
}

static int is_sorted(const int v[], unsigned int n)
{
	unsigned int i;

	for (i = 1; i < n; i++) {
		if (v[i] < v[i - 1])
			return 0;
	}

	return 1;
}

enum {
	SIZE = 100000
};

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

int main(int argc, char *argv[])
{
	struct {
		const char *name;
		void (*sort)(int[], unsigned int);
	} sorts[] = {
		{ "treesort", treesort },
		{ "our quicksort", library_quicksort },
		{ "library quicksort", library_quicksort }
	};
	int v[SIZE];
	time_t seed;
	clock_t start, end;
	unsigned int i;

	seed = time(NULL);

	for (i = 0; i < NELEMS(sorts); i++) {
		srand(seed);
		fill_random(v, SIZE);
		start = clock();
		sorts[i].sort(v, SIZE);
		end = clock();
		printf("%s: %.3f\n", sorts[i].name,
			(double) (end - start) / CLOCKS_PER_SEC);
		if (!is_sorted(v, SIZE))
			printf("Not sorted!\n");
	}

	return 0;
}

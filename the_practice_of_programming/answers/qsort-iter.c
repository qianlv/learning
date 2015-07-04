#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	MAX_STACK_DEPTH = 100
};

/* This data structure keeps track of what portion of an array is currently
   being sorted. */
struct qsort_state {
	int start;
	int end;
};

void qsort_state_stack_push(struct qsort_state *stack, int *depth,
	int start, int end)
{
	if (*depth >= MAX_STACK_DEPTH) {
		fprintf(stderr, "Maximum stack depth of %d exceeded.\n", MAX_STACK_DEPTH);
		exit(1);
	}
	stack[*depth].start = start;
	stack[*depth].end = end;
	(*depth)++;
}

void qsort_state_stack_pop(struct qsort_state *stack, int *depth,
	int *start, int *end)
{
	if (*depth <= 0) {
		fprintf(stderr, "Stack underflow.\n");
		exit(1);
	}
	(*depth)--;
	*start = stack[*depth].start;
	*end = stack[*depth].end;
}

void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* Iterative Quicksort: sort v[0]..v[n - 1] into increasing order. */
void qsort_iter(int v[], int n)
{
	struct qsort_state stack[MAX_STACK_DEPTH];
	int depth = 0;

	qsort_state_stack_push(stack, &depth, 0, n);
	while (depth > 0) {
		int i, last;
		int start, end;
		qsort_state_stack_pop(stack, &depth, &start, &end);
		if (end - start <= 1)
			continue;
		/* Move the pivot. */
		swap(v, start, start + rand() % (end - start));
		last = start;
		/* Parition. */
		for (i = start + 1; i < end; i++) {
			if (v[i] < v[start])
				swap(v, ++last, i);
		}
		/* Restore the pivot. */
		swap(v, start, last);
		qsort_state_stack_push(stack, &depth, last + 1, end);
		qsort_state_stack_push(stack, &depth, start, last);
	}
}

int is_sorted(int v[], int n)
{
	int i;

	for (i = 0; i < n - 1; i++) {
		if (v[i] > v[i + 1])
			return 0;
	}

	return 1;
}

/* Returns true if the array a is a permutation of the array b. */
int is_permuted_array(int a[], int b[], int n)
{
	int *t;
	int i, j;

	t = malloc(n * sizeof(int));
	if (t == NULL) {
		perror("is_permuted_array");
		exit(1);
	}
	memset(t, 0, n * sizeof(int));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (a[i] == b[j] && !t[j]) {
				t[j] = 1;
				break;
			}
		}
		if (j == n)
			return 0;
	}
	free(t);

	return 1;
}

int *duplicate_array(int v[], int n)
{
	int *a;

	a = malloc(n * sizeof(int));
	if (a == NULL)
		return NULL;
	memcpy(a, v, n * sizeof(int));

	return a;
}

void print_array(int v[], int n)
{
	int i;

	printf("{");
	if (n > 0)
		printf(" %d", v[0]);
	for (i = 1; i < n; i++)
		printf(", %d", v[i]);
	printf(" }\n");
}

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

int main(int argc, char *argv[])
{
	int test_1[] = { 1 };
	int test_2[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int test_3[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int test_4[] = { 0, 0, 0, 0, 4, 0, 0, 3 };
	int test_5[20];
	int test_6[10000];
	struct {
		int *v;
		int n;
	} test_cases[] = {
		{ test_1, NELEMS(test_1) },
		{ test_2, NELEMS(test_2) },
		{ test_3, NELEMS(test_3) },
		{ test_4, NELEMS(test_4) },
		{ test_5, NELEMS(test_5) },
		{ test_6, NELEMS(test_6) },
	};
	int i;

	for (i = 0; i < NELEMS(test_5); i++)
		test_5[i] = rand() % 100 - 50;
	for (i = 0; i < NELEMS(test_6); i++)
		test_6[i] = rand();

	for (i = 0; i < NELEMS(test_cases); i++) {
		int *a, *v;
		int n;

		v = test_cases[i].v;
		n = test_cases[i].n;
		a = duplicate_array(v, n);
		if (a == NULL) {
			perror("Can't duplicate array");
			exit(1);
		}
		qsort_iter(a, n);
		if (n < 100) {
			print_array(v, n);
			print_array(a, n);
		}
		printf("Test %u: ", i + 1);
		if (!is_sorted(a, n))
			printf("FAILED: not sorted.\n");
		else if (!is_permuted_array(a, v, n))
			printf("FAILED: different contents.\n");
		else
			printf("passed.\n");

		free(a);
	}

	return 0;
}

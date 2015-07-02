#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void fill_zero(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		v[i] = 0;
}

static void fill_ascending(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		v[i] = i;
}

static void fill_descending(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		v[i] = n - i;
}

static void fill_onoff(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		v[i] = i % 2;
}

static void fill_ramp(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		v[i] = i % 10;
}

static void fill_interleaved(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; 2 * i < n; i += 2)
		v[2 * i] = i;
	for (i = 0; 2 * i + 1 < n; i += 2)
		v[2 * i + 1] = n / 2 + i;
}

static void fill_interleaved_reversed(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; 2 * i < n; i += 2)
		v[2 * i] = i;
	for (i = 0; 2 * i + 1 < n; i += 2)
		v[n - 2 * i] = n / 2 + i;
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

enum {
	SIZE = 1000000
};

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

int main(int argc, char *argv[])
{
	struct {
		const char *name;
		void (*fill)(int v[], unsigned int n);
	} test_cases[] = {
		{ "zero", fill_zero },
		{ "ascending", fill_ascending },
		{ "descending", fill_descending },
		{ "onoff", fill_onoff },
		{ "ramp", fill_ramp },
		{ "interleaved", fill_interleaved },
		{ "interleaved-reversed", fill_interleaved_reversed }
	};
	clock_t start, end;
	int v[SIZE];
	unsigned int i;

	for (i = 0; i < NELEMS(test_cases); i++) {
		test_cases[i].fill(v, SIZE);
		start = clock();
		qsort(v, SIZE, sizeof(v[0]), cmp_int);
		end = clock();
		printf("%-12s: %.3f s\n", test_cases[i].name,
			(double) (end - start) / CLOCKS_PER_SEC);
	}

	return 0;
}

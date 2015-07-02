#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* genrand: generate a random number in [0, n) as if selecting from a list of
   length n (pretending that the length is not known in advance). Use rand as
   the base random number generator. */
int genrand(int (*rand)(void), int n)
{
	int i;
	int r;

	r = 0;
	for (i = 0; i < n; i++) {
		if (rand() % (i + 1) == 0)
			r = i;
	}

	return r;
}

/* rand_even: stdlib rand purposely broken to return only even numbers. */
int rand_even(void)
{
	int r;

	do {
		r = rand();
	} while (r % 2 != 0);

	return r;
}

/* rand_lcong: a bogus linear congruential generator with constants I made
   up. */
int rand_lcong(void)
{
	static int r = 10;

	r = r * 12345 + 8432726;

	return r;
}

int rand_stupid(void)
{
	return 0;
}

#define LIST_LEN 100

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

void clear_array(int array[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		array[i] = 0;
}

void print_histogram(int array[], int n)
{
	int i, j;
	int num_width;

	num_width = snprintf(NULL, 0, "%d", n);
	for (i = 0; i < n; i++) {
		printf("%*d:", num_width, i);
		for (j = 0; j < array[i]; j++)
			printf("#");
		printf(" %d\n", j);
	}
}

int main(int argc, char *argv[])
{
	struct {
		const char *name;
		int (*fn)(void);
	} rands[] = {
		{ "rand", rand },
		{ "rand_even", rand_even },
		{ "rand_lcong", rand_lcong },
		{ "rand_stupid", rand_stupid },
	};
	int list[LIST_LEN];
	int i, j;

	srand(0);

	for (i = 0; i < NELEMS(rands); i++) {
		if (i > 0)
			printf("\n");
		clear_array(list, LIST_LEN);
		for (j = 0; j < LIST_LEN * 10; j++)
			list[genrand(rands[i].fn, LIST_LEN)]++;
		printf("%s\n", rands[i].name);
		print_histogram(list, LIST_LEN);
	}

	return 0;
}

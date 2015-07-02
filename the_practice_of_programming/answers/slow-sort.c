/*
This sort algorithm is a classic bogosort, with the addition of a slow is_sorted
check. Random permutations of the initial sequence are tested until one is found
that is in order.

The slow is_sorted test checks to see that every proper subsequence of a
sequence is sorted. Naturally, those subsequences are checked recursively in the
same way. A great amount of pointless recomputation is done. Its correctness
rests on the following theorem.

Definition: a sequence s of length n is sorted if, for every i and j in
[ 1, 2, ..., n ], if i < j then s_i <= s_j.

Definition: a proper subsequence of a sequence s (of length n) is any sequence
b_x = s_c_x where c is any subset of { 1, 2, ..., n } such that if i < j then
c_i < c_j. (In short, a proper subsequence is obtained from an original sequence
just by removing one or more elements.)

Theorem: a sequence of length 3 or greater is sorted if and only if each of its
proper subsequences is sorted.
Proof: Let s_1 .. s_n be a sorted sequence. Let { c_1 .. c_m } be a proper
subset of { 1, 2, ..., n } such that c_i < c_j if i < j. Let b_1 .. b_m be the
subsequence of obtained by taking b_x = s_c_x. Let i and j be given such that
1 <= i < j <= n. Then c_i < c_j, hence s_c_i <= s_c_j, or in other words
b_i <= b_j. This is true for any subsequence b of s because the subset { c }
was not specified.
Let s_1 .. s_n be a sequence of length 3 or greater and assume that every one of
its proper subsequences is sorted. Let 1 <= i < j <= n be given. s has a proper
subsequence of length at least 2 that contains s_i and s_j. By the assumption
that the subsequences are sorted, s_i <= s_j.

To ease analysis I ignore the random generation of permutations and pretend that
each permutation is generated once. I don't know the time complexity of the
algorithm in closed form, but as a recurrence it's something like
T(n) = sum(i .. n - 1, choose(n, i) * T(i)). The complexity must be more than
Omega((2^n) * n!), because O(2^n) recursive calls are made just at the first
level of is_sorted. See very_slow_sort for a trivial pessimization.

An idea for improvement would be on every iteration to generate every possible
permutation of the sequence, and then pick one at random. This would require
O(n * n!) steps just to write the permutations and well as requiring a fantastic
amount of memory.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int verbose = 1;

static void *safe_malloc(size_t size)
{
	void *p;

	errno = 0;
	p = malloc(size);
	if (p == NULL) {
		fprintf(stderr, "safe_malloc failed: %s.\n", strerror(errno));
		exit(1);
	}

	return p;
}

/* We use a data structure called a bit set to keep track of subsequences. A
   bit set is essentially a non-negative integer of fixed but unbounded size.
   Whether a bit is on or off in the binary representation of the integer
   determines whether the corresponding element is in the subsequence. */

typedef unsigned int bit_set_t;

#define BITS_IN(type) (sizeof(type) * 8)

static bit_set_t *bit_set_new(unsigned int num_bits)
{
	bit_set_t *set;
	size_t length;

	length = (num_bits + BITS_IN(bit_set_t) - 1) / BITS_IN(bit_set_t);
	set = safe_malloc(length * sizeof(bit_set_t));
	memset(set, 0, length * sizeof(bit_set_t));

	return set;
}

static void bit_set_free(bit_set_t *set)
{
	free(set);
}

/* Return the value of bit n in the set. */
static int bit_set_is_set(const bit_set_t *set, unsigned int n)
{
	return (set[n / BITS_IN(bit_set_t)] & (1 << (n % BITS_IN(bit_set_t)))) != 0;
}

/* Increment a bit set; i.e., increase the integer it represents by 1. This is
   used to run through all possible subsets. */
static void bit_set_increment(bit_set_t *set, unsigned int num_bits)
{
	unsigned int i;
	size_t length;

	length = (num_bits + BITS_IN(bit_set_t) - 1) / BITS_IN(bit_set_t);
	for (i = 0; i < length; i++) {
		set[i]++;
		if (set[i] != 0)
			break;
	}
}

/* Return a count of all 1 bits in the set. */
static unsigned int bit_set_count(bit_set_t *set, unsigned int num_bits)
{
	unsigned int i, count;

	count = 0;
	for (i = 0; i < num_bits; i++)
		count += bit_set_is_set(set, i);

	return count;
}

static int is_sorted(int v[], unsigned int n)
{
	bit_set_t *set;
	int *sub;
	unsigned int i, j, count;
	int sorted, sub_sorted;

	if (n == 0 || n == 1)
		return 1;
	if (n == 2)
		return v[1] >= v[0];

	/* Start by assuming everything is sorted. */
	sorted = 1;

	set = bit_set_new(n);

	/* For every proper subsequence. */
	while ((count = bit_set_count(set, n)) < n) {
		sub = safe_malloc(count * sizeof(int));
		for (i = 0, j = 0; i < n && j < count; i++) {
			if (bit_set_is_set(set, i))
				sub[j++] = v[i];
		}
		sub_sorted = is_sorted(sub, count);
		free(sub);
		sorted = sorted && sub_sorted;
		bit_set_increment(set, n);
	}

	bit_set_free(set);

	return sorted;
}

static void fill_random(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		v[i] = rand();
}

static void swap(int v[], unsigned int i, unsigned int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

static void permute(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 1; i < n; i++)
		swap(v, i, rand() % (i + 1));
}

static void slow_sort(int v[], unsigned int n)
{
	unsigned long long count;

	count = 0;
	while (!is_sorted(v, n)) {
		count++;
		if (verbose)
			printf("Nope (try %llu).\n", count);
		permute(v, n);
	}
	printf("Yep.\n");
}

/* A trivial pessimization of slow_sort. */
static void very_slow_sort(int v[], unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		slow_sort(v, i);
}

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

#define SIZE 7

int main(int argc, char *argv[])
{
	int array[SIZE];

	srand(time(NULL));

	fill_random(array, NELEMS(array));

	slow_sort(array, NELEMS(array));

	return 0;
}

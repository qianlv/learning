/* Test scaffold for mem... family functions */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

enum {
	LEFT_MARGIN = 256,
	RIGHT_MARGIN = 256,
	MAX_N = 65537,
	ARRAY_SIZE = LEFT_MARGIN + MAX_N + RIGHT_MARGIN,
};

/* safe_memset: set first bytes of s to c */
static void *safe_memset(void *s, int c, size_t n)
{
	size_t i;
	char *p;

	p = (char *) s;
	for (i = 0; i < n; i++)
		p[i] = c;
	return s;
}

/* safe_memmove: copy bytes, overlap permitted */
static void *safe_memmove(void *to, const void *from, size_t n)
{
	static char buf[MAX_N];
	char *t = to;
	size_t i;

	assert(n <= sizeof(buf));
	for (i = 0; i < n; i++)
		buf[i] = ((char *) from)[i];
	for (i = 0; i < n; i++)
		t[i] = buf[i];
	return to;
}

/* safe_memcmp: compare bytes */
static int safe_memcmp(const void *a1, const void *a2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++) {
		int d;
		d = ((unsigned char *) a1)[i] - ((unsigned char *) a2)[i];
		if (d != 0)
			return d;
	}
	return 0;
}

/* return true if n > 0 is a power of 2 */
static int is_power_2(unsigned int n)
{
	return (n & (n - 1)) == 0;
}

/* get the next power of 2 > n */
static unsigned int next_power_2(unsigned int n)
{
	unsigned int t = 1;

	for (; n > 0; n >>= 1)
		t <<= 1;
	return t;
}

/* given a previous test n value, get the next */
static size_t get_next_n(size_t prev)
{
	if (prev == (size_t) -1)
		return 0;
	if (prev < 9)
		return prev + 1;
	if (is_power_2(prev + 1))
		return prev + 1;
	if (is_power_2(prev))
		return prev + 1;
	return next_power_2(prev) - 1;
}

static char s0[ARRAY_SIZE], s1[ARRAY_SIZE];

static int memset_values[] = { 0, 1, 0x7F, 0x80, 0xFF, 0x11223344 };

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

void test_memset(void)
{
	size_t n;
	int offset, i;
	char *r0, *r1;

	for (offset = 0; offset <= 10; offset++) {
		for (n = 0; n <= MAX_N; n = get_next_n(n)) {
			for (i = 0; i < NELEMS(memset_values); i++) {
				int c = memset_values[i];
				printf("memset(p + %d, 0x%02X, %u)\n", offset, c, (unsigned int) n);
				safe_memset(s0, ~c, ARRAY_SIZE);
				safe_memset(s1, ~c, ARRAY_SIZE);
				r0 = safe_memset(s0 + LEFT_MARGIN + offset, c, n);
				r1 = memset(s1 + LEFT_MARGIN + offset, c, n);
				assert(r0 - s0 == r1 - s1);
				assert(safe_memcmp(s0, s1, ARRAY_SIZE) == 0);
			}
		}
	}
}

/* fill test arrays with a pseudorandom test pattern */
static void setup_pattern(void)
{
	const unsigned int m = 65537, a = 5, c = 7;
	unsigned int i, n;

	n = 0;
	for (i = 0; i < ARRAY_SIZE; i++) {
		n = (n * a + c) % m;
		s0[i] = n;
		s1[i] = n;
	}
}

/* check memmove-like fn aginst safe_memmove, in both directions */
static void check_copy(void *(*fn)(void *, const void *, size_t),
	ptrdiff_t to, ptrdiff_t from, size_t n)
{
	char *r0, *r1;

	printf("(%d, %d, %u)\n", (int) to, (int) from, (unsigned int) n);
	setup_pattern();
	r0 = safe_memmove(s0 + LEFT_MARGIN + to, s0 + LEFT_MARGIN + from, n);
	r1 = fn(s1 + LEFT_MARGIN + to, s1 + LEFT_MARGIN + from, n);
	assert(r0 - s0 == r1 - s1);
	assert(safe_memcmp(s0, s1, ARRAY_SIZE) == 0);

	printf("(%d, %d, %u)\n", (int) from, (int) to, (unsigned int) n);
	setup_pattern();
	r0 = safe_memmove(s0 + LEFT_MARGIN + from, s0 + LEFT_MARGIN + to, n);
	r1 = fn(s1 + LEFT_MARGIN + from, s1 + LEFT_MARGIN + to, n);
	assert(r0 - s0 == r1 - s1);
	assert(safe_memcmp(s0, s1, ARRAY_SIZE) == 0);
}

/* test memmove-like fn, optionally allowing overlap */
void test_copy(void *(*fn)(void *, const void *, size_t), int overlap)
{
	int off0, off1;
	size_t n;

	for (off0 = 0; off0 <= 10; off0++) {
		for (off1 = 0; off0 + off1 <= MAX_N; off1 = (off1 == 0) ? 1 : off1 << 1) {
			for (n = 0; off0 + off1 + n <= MAX_N; n = get_next_n(n)) {
				if (!overlap && n > off1)
					break;
				check_copy(fn, off0, off0 + off1, n);
			}
		}
	}
}

void test_memcpy(void)
{
	printf("memcpy\n");
	test_copy(memcpy, 0);
}

void test_memmove(void)
{
	printf("memmove\n");
	test_copy(memmove, 1);
}

static int sign(n)
{
	if (n < 0)
		return -1;
	else if (n > 0)
		return 1;
	else
		return 0;
}

void test_memcmp(void)
{
	int off0, off1, n;
	int r0, r1;

	setup_pattern();
	for (off0 = 0; off0 <= 10; off0++) {
		for (off1 = off0; off1 <= 10; off1++) {
			for (n = 0; off1 + n <= MAX_N; n = get_next_n(n)) {
				printf("memcmp(p + %d, p + %d, %u)\n", off0, off1, n);
				r0 = safe_memcmp(s0 + LEFT_MARGIN + off0, s0 + LEFT_MARGIN + off1, n);
				r1 = memcmp(s0 + LEFT_MARGIN + off0, s0 + LEFT_MARGIN + off1, n);
				assert(sign(r0) == sign(r1));
				printf("memcmp(p + %d, p + %d, %u)\n", off1, off0, n);
				r0 = safe_memcmp(s0 + LEFT_MARGIN + off1, s0 + LEFT_MARGIN + off0, n);
				r1 = memcmp(s0 + LEFT_MARGIN + off1, s0 + LEFT_MARGIN + off0, n);
				assert(sign(r0) == sign(r1));
			}
		}
	}
}

int main(void)
{
	test_memset();
	test_memcpy();
	test_memmove();
	test_memcmp();

	return 0;
}

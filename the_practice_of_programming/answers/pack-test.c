#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "eprintf.h"
#include "pack.h"

static const char *DEFAULT_IN_FILENAME = "pack.in";
static const char *DEFAULT_OUT_FILENAME = "pack.out";

ulong read_count(char **bp);

static void print_vargs(char *fmt, va_list args)
{
	char *p;
	int c;
	ulong l;
	ulong count;
	int is_first = 1;

	for (p = fmt; *p != '\0'; p++) {
		for (count = read_count(&p); *p != '\0' && count > 0; count--) {
			if (!is_first)
				printf(", ");
			is_first = 0;
			switch (*p) {
			case 'c':
				c = va_arg(args, int);
				if (isprint(c))
					printf("'%c'", c);
				else
					printf("(char) 0x%02X", c);
				break;
			case 's':
				printf("%u", va_arg(args, unsigned int));
				break;
			case 'S':
				printf("%d", va_arg(args, int));
				break;
			case 'l':
				printf("%lu", va_arg(args, unsigned long));
				break;
			case 'L':
				printf("%ld", va_arg(args, long));
				break;
			case '$':
				l = va_arg(args, ulong);
				printf("%ld, \"%.*s\"", l, (int) l, va_arg(args, char *));
				break;
			default:
				eprintf("Illegal format character 0x%02X", *p);
				break;
			}
		}
	}
}

static void print_args(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	print_vargs(fmt, args);
	va_end(args);
}

static void verbose_pack(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	printf("pack(buf, \"%s\", ", fmt);
	print_vargs(fmt, args);
	printf(")\n");
	va_end(args);
}

#define CHECK_VALUE(v, expected, fmt) { \
	if ((v) != (expected)) \
		weprintf("Value " fmt " doesn't match expected " fmt "", (v), (expected)); \
}

#define CHECK_STRING(s, expected, len) { \
	if (memcmp((s), (expected), (len)) != 0) \
		weprintf("String \"%s\" doesn't match expected \"%s\"", (s), (expected)); \
}

/* test_file: test storage and retrieval of packed values in a file */
static void test_file(const char *in_filename, const char *out_filename)
{
	FILE *in_fp, *out_fp;
	uchar buf[128];
	int i, n;

	char c;
	unsigned short us;
	short ss1, ss2;
	unsigned long ul;
	long sl1, sl2;

	printf("test_file\n");

	in_fp = fopen(in_filename, "rb");
	if (in_fp == NULL)
		eprintf("Error opening %s for input", in_filename);
	n = fread(buf, 1, sizeof(buf), in_fp);
	fclose(in_fp);

	i = unpack(buf, "csSSlLL", &c, &us, &ss1, &ss2, &ul, &sl1, &sl2);
	if (i == -1)
		eprintf("unpack failed");
	if (i != n)
		eprintf("unpack processed %d bytes, expected %d", i, n);

	printf("Read %d bytes from %s: ", n, in_filename);
	print_args("csSSlLL", c, us, ss1, ss2, ul, sl1, sl2);
	printf("\n");

	CHECK_VALUE(c, '!', "%c")
	CHECK_VALUE(us, 45, "%u")
	CHECK_VALUE(ss1, -1, "%d")
	CHECK_VALUE(ss2, 10, "%d")
	CHECK_VALUE(ul, 65537, "%lu")
	CHECK_VALUE(sl1, -12, "%ld")
	CHECK_VALUE(sl2, 123, "%ld")

	verbose_pack("csSSlLL", '!', 45, -1, 10, 65537, -12, 123);
	n = pack(buf, "csSSlLL", '!', 45, -1, 10, 65537, -12, 123);
	if (n == -1)
		eprintf("pack failed");

	out_fp = fopen(out_filename, "wb");
	if (out_fp == NULL)
		eprintf("Error opening %s for writing", out_filename);
	if (fwrite(buf, 1, n, out_fp) != n)
		eprintf("Error writing buffer");
	fclose(out_fp);
	printf("Wrote %d bytes to %s.\n", n, out_filename);
}

/* test_string: test packing strings */
static void test_string(void)
{
	uchar buf[128];
	int i, n;

	char c1, c2, c3;
	char s1[10], s2[10], s3[10];

	printf("test_string\n");

	verbose_pack("c2$c$c", '#', 6, "Hello", 10, "zero\0byte", '!', 4, "abc", '?');
	n = pack(buf, "c2$c$c", '#', 6, "Hello", 10, "zero\0byte", '!', 4, "abc", '?');
	if (n == -1)
		eprintf("pack failed");
	i = unpack(buf, "c2$c$c", &c1, sizeof(s1), s1, sizeof(s2), s2, &c2, sizeof(s3), s3, &c3);
	if (i == -1)
		eprintf("unpack failed");
	if (i != n)
		eprintf("pack %d bytes doesn't match unpack %d bytes", n, i);
	CHECK_VALUE(c1, '#', "%c")
	CHECK_STRING(s1, "Hello", 6)
	CHECK_STRING(s2, "zero\0byte", 10)
	CHECK_VALUE(c2, '!', "%c")
	CHECK_STRING(s3, "abc", 4)
	CHECK_VALUE(c3, '?', "%c")
}

/* test_repeat: test repetition counts */
static void test_repeat(void)
{
	uchar buf[128];
	const char *aa = "abcdefghijklmnopqrstuvwxyz";
	int i, n;

	ushort us;
	long sl1, sl2, sl3;
	char cc[26];

	printf("test_repeat\n");

	verbose_pack("1s0c3L", 5, -1000, 45678, 999);
	n = pack(buf, "1s0c3L", 5, -1000, 45678, 999);
	if (n == -1)
		eprintf("pack failed");
	i = unpack(buf, "1s0c3L", &us, &sl1, &sl2, &sl3);
	if (i == -1)
		eprintf("unpack failed");
	if (i != n)
		eprintf("pack %d bytes doesn't match unpack %d bytes", n, i);
	CHECK_VALUE(us, 5, "%u")
	CHECK_VALUE(sl1, -1000, "%ld")
	CHECK_VALUE(sl2, 45678, "%ld")
	CHECK_VALUE(sl3, 999, "%ld")

	verbose_pack("26c", aa[0], aa[1], aa[2], aa[3], aa[4],
		aa[5], aa[6], aa[7], aa[8], aa[9],
		aa[10], aa[11], aa[12], aa[13], aa[14],
		aa[15], aa[16], aa[17], aa[18], aa[19],
		aa[20], aa[21], aa[22], aa[23], aa[24], aa[25]);
	n = pack(buf, "26c", aa[0], aa[1], aa[2], aa[3], aa[4],
		aa[5], aa[6], aa[7], aa[8], aa[9],
		aa[10], aa[11], aa[12], aa[13], aa[14],
		aa[15], aa[16], aa[17], aa[18], aa[19],
		aa[20], aa[21], aa[22], aa[23], aa[24], aa[25]);
	if (n == -1)
		eprintf("pack failed");
	i = unpack(buf, "26c", cc, cc + 1, cc + 2, cc + 3, cc + 4,
		cc + 5, cc + 6, cc + 7, cc + 8, cc + 9,
		cc + 10, cc + 11, cc + 12, cc + 13, cc + 14,
		cc + 15, cc + 16, cc + 17, cc + 18, cc + 19,
		cc + 20, cc + 21, cc + 22, cc + 23, cc + 24, cc + 25);
	if (i == -1)
		eprintf("unpack failed");
	if (i != n)
		eprintf("pack %d bytes doesn't match unpack %d bytes", n, i);
	CHECK_STRING(aa, cc, 26)

	if (pack(buf, "-20c", '!') != -1)
		eprintf("negative count not properly rejected");
}

/* pack-test main: read packed data from input, check that is is correct, write
   it to output */
int main(int argc, char *argv[])
{
	const char *in_filename, *out_filename;

	if (argc > 1)
		in_filename = argv[1];
	else
		in_filename = DEFAULT_IN_FILENAME;
	if (argc > 2)
		out_filename = argv[2];
	else
		out_filename = DEFAULT_OUT_FILENAME;

	test_file(in_filename, out_filename);
	test_string();
	test_repeat();

	return 0;
}

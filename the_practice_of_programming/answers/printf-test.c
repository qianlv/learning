#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "eprintf.h"

int io[2];
FILE *w;

int test_printf(const char *expected, const char *fmt, ...)
{
	char buf[BUFSIZ];
	va_list args;
	size_t n, len;
	ssize_t i;

	va_start(args, fmt);
	n = vfprintf(w, fmt, args);
	va_end(args);

	fflush(w);

	len = 0;
	while ((i = read(io[0], buf + len, sizeof(buf) - len - 1)) > 0)
		len += i;
	buf[len] = '\0';

	if (i == -1 && errno != EAGAIN)
		eprintf("Error from read: %d.", errno);

	if (n != len) {
		fprintf(stderr, "Length error on \"%s\": wrote %u, read %u.\n",
			fmt, (unsigned int) n, (unsigned int) len);
		return 0;
	}
	if (strcmp(buf, expected) != 0) {
		fprintf(stderr, "Error on \"%s\": expected \"%s\", got \"%s\".\n",
			fmt, expected, buf);
		return 0;
	}

	return 1;
}

static void set_nonblock(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
}

int main(void)
{
	int n;

	if (pipe(io) != 0)
		eprintf("Error creating pipe.");
	set_nonblock(io[0]);
	w = fdopen(io[1], "w");
	if (w == NULL)
		eprintf("Error creating write stream.");

	test_printf("%", "%%");
	test_printf("1", "%d", 1);
	test_printf("+1", "%+d", 1);
	test_printf("1 ", "%-2d", 1);
	test_printf(" 1", "%2d", 1);
	test_printf("1  ", "%-3d", 1);
	test_printf("  1", "%3d", 1);
	test_printf("-1", "%d", -1);

	test_printf("1", "%i", 1);
	test_printf("+1", "%+i", 1);
	test_printf("1 ", "%-2i", 1);
	test_printf(" 1", "%2i", 1);
	test_printf("1  ", "%-3i", 1);
	test_printf("  1", "%3i", 1);
	test_printf("-1", "%i", -1);

	test_printf("13", "%o", 013);

	test_printf("be24", "%x", 0xBE24);
	test_printf("BE24", "%X", 0xBE24);

	test_printf("1", "%u", 1);
	test_printf("A", "%c", 'A');
	test_printf("A", "%.5c", 'A');
	test_printf(" A", "%2c", 'A');
	test_printf("Hello", "%s", "Hello");
	test_printf("Hello", "%3s", "Hello");
	test_printf("  Hello", "%7s", "Hello");
	test_printf("  Hel", "%5.3s", "Hello");
	test_printf("Hel", "%.*s", 3, "Hello");
	test_printf("  Hello", "%*s", 7, "Hello");
	test_printf("  Hel", "%*.*s", 5, 3, "Hello");

	test_printf("1.200000", "%f", 1.2);
	test_printf("1", "%.0f", 1.2);
	test_printf("1.2", "%.1f", 1.2);
	test_printf("1.200", "%.3f", 1.200);
	test_printf("1.200", "%5.3f", 1.200);
	test_printf("   1.200", "%8.3f", 1.200);

	test_printf("1.200000e+00", "%e", 1.200);
	test_printf("1.2e+00", "%.1e", 1.200);
	test_printf("1.0e+00", "%.1e", 1.0);
	test_printf("-5.5e-03", "%.1e", -0.0055);
	test_printf("1.200000E+00", "%E", 1.200);
	test_printf("1.2E+00", "%.1E", 1.200);
	test_printf("1.0E+00", "%.1E", 1.0);
	test_printf("-5.5E-03", "%.1E", -0.0055);

	test_printf("1.3", "%g", 1.3);
	test_printf("0.00013", "%g", 1.3e-4);
	test_printf("1.3e-05", "%g", 1.3e-5);
	test_printf("1.3e+07", "%g", 1.3e7);
	test_printf("13000000", "%.8g", 1.3e7);
	test_printf("1.3", "%G", 1.3);
	test_printf("0.00013", "%G", 1.3e-4);
	test_printf("1.3E-05", "%G", 1.3e-5);
	test_printf("1.3E+07", "%G", 1.3e7);
	test_printf("13000000", "%.8G", 1.3e7);

	test_printf("abc", "abc%n", &n);
	if (n != 3)
		fprintf(stderr, "%%n failed; expected %d, got %d.\n", 3, n);

	fclose(w);

	return 0;
}

/* Test the ctime function around the Y2K boundary. */

/* For strptime, not part of ANSI C. */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* The length of a string returned by ctime. */
#define CTIME_LENGTH 25

static void test_ctime_length(time_t t)
{
	char *s;
	size_t len;

	s = ctime(&t);
	len = strlen(s);
	if (len != CTIME_LENGTH) {
		printf("ctime string has wrong length %u (should be %u).\n",
			(unsigned int) len, (unsigned int) CTIME_LENGTH);
		printf("%s", s);
		exit(1);
	}
	if (s[CTIME_LENGTH - 1] != '\n') {
		printf("Last character of ctime string is not '\\n'.\n");
		printf("%s", s);
		exit(1);
	}
}

static void test_ctime_roundtrip(time_t t)
{
	struct tm tm = { 0 };
	time_t u;
	char *s;

	s = ctime(&t);
	if (strptime(s, "%a %b %d %H:%M:%S %Z %Y", &tm) == NULL) {
		fprintf(stderr, "Error parsing time string: %s", s);
		exit(1);
	}
	u = mktime(&tm);
	if (u == (time_t) (-1)) {
		fprintf(stderr, "Error in mktime.\n");
		exit(1);
	}
	if (t != u) {
		printf("Mismatch: %lu -> \"%s\" -> %lu\n", t, s, u);
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	struct tm tm;
	time_t t;
	int i;

	tm.tm_year = 99;
	tm.tm_mon = 11;
	tm.tm_mday = 31;
	tm.tm_hour = 23;
	tm.tm_min = 59;
	tm.tm_sec = 30;

	t = mktime(&tm);

	for (i = 0; i < 60; i++) {
		char *s = ctime(&t);
		printf("%s", s);
		test_ctime_length(t);
		test_ctime_roundtrip(t);
		t++;
	}

	return 0;
}

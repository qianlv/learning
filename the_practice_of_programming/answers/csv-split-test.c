#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "csv.h"

/* test getting all fields */
void test_all(FILE *fp)
{
	char *line;
	int i;

	while ((line = csvgetline(fp)) != NULL) {
		for (i = 0; i < csvnfield(); i++)
			csvfield(i);
	}
}

/* test calling csvgetline but not getting any fields */
void test_none(FILE *fp)
{
	char *line;

	while ((line = csvgetline(fp)) != NULL)
		;
}

/* test getting just the first field without calling csvnfield */
void test_first(FILE *fp)
{
	char *line;

	while ((line = csvgetline(fp)) != NULL)
		csvfield(0);
}

/* test repeatedly getting a single element */
void test_repeated(FILE *fp)
{
	char *line;

	while ((line = csvgetline(fp)) != NULL) {
		int nfield = csvnfield();

		csvfield(nfield / 2);
		csvfield(nfield / 2);
		csvfield(nfield / 2);
	}
}

int main(int argc, char *argv[])
{
	struct {
		const char *name;
		void (*f)(FILE *);
	} TESTS[] = {
		{ "all", test_all }, 
		{ "none", test_none }, 
		{ "first", test_first }, 
		{ "repeated", test_repeated }, 
	};
	char *filename;
	FILE *fp;
	clock_t start, end;
	int i;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(1);
	}
	filename = argv[1];
	fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Couldn't open %s.\n", filename);
		exit(1);
	}

	for (i = 0; i < sizeof(TESTS) / sizeof(TESTS[0]); i++) {
		fseek(fp, 0, SEEK_SET);
		start = clock();
		TESTS[i].f(fp);
		end = clock();
		printf("%s: %.2f s\n", TESTS[i].name,
			(double) (end - start) / CLOCKS_PER_SEC);
	}

	fclose(fp);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Test the checking malloc and free. This is meant to be linked with
   safe-malloc.c. */
int main(int argc, char *argv[])
{
	int testno;
	char *p;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s testno\n", argv[0]);
		fprintf(stderr, "testno is 0-3 for a malloc test to run.\n");
		fprintf(stderr, "0: overwrite beginning of block.\n");
		fprintf(stderr, "1: overwrite end of block.\n");
		fprintf(stderr, "2: free uninitialized pointer.\n");
		fprintf(stderr, "3: double free.\n");
		exit(0);
	}

	testno = atoi(argv[1]);

	/* None of these are expected to succeed. */
	switch (testno) {
		case 0:
			/* overwrite beginning */
			p = malloc(10);
			memset(p - 5, 0, 10);
			free(p);
			break;
		case 1:
			/* write past end */
			p = malloc(10);
			memset(p, 0, 20);
			free(p);
			break;
		case 2:
			/* free unintialized pointer */
			free(p);
			break;
		case 3:
			/* double free */
			p = malloc(10);
			free(p);
			free(p);
			break;
		default:
			printf("%s: Invalid test number %s.\n", argv[0], argv[1]);
			break;
	}

	return 0;
}

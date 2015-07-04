#include <stdio.h>

enum { DEBUG = 0 };

static int debug(void)
{
	return DEBUG;
}

int main(void)
{
	if (DEBUG) {
		printf("if (DEBUG)\n");
		/* syntax error */
	}
	if (!DEBUG) {
		printf("if (!DEBUG)\n");
		/* syntax error */
	}
	if (debug()) {
		printf("if (debug())\n");
		/* syntax error */
	}
	if (!debug()) {
		printf("if (!debug())\n");
		/* syntax error */
	}
	if (0) {
		printf("if (0)\n");
		/* syntax error */
	}
	if (!0) {
		printf("if (!0)\n");
		/* syntax error */
	}

	return 0;
}

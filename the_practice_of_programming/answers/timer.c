#include <time.h>

static clock_t clock_start;

void timer_start(void)
{
	clock_start = clock();
}

double timer_elapsed(void)
{
	return ((double) clock() - clock_start) / CLOCKS_PER_SEC;
}

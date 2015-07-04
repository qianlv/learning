#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timer.h"

#define N 1000

int main(void)
{
	DIR *d;
	int i;

	timer_start();

	for (i = 0; i < N; i++) {
		errno = 0;
		d = opendir(".");
		if (d == NULL) {
			fprintf(stderr, "Error in opendir: %s\n", strerror(errno));
			exit(1);
		}
		while (readdir(d) != NULL)
			;
		closedir(d);
	}

	printf("%g s\n", timer_elapsed());

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nameval Nameval;
struct Nameval {
	char	*name;
	int	value;
};

struct NVtab {
	int nval;	/* current number of values */
	int max;	/* allocated number of values */
	Nameval *nameval;	/* array of name-value pairs */
} nvtab;

enum { NVINIT = 1, NVGROW = 2 };

/* addname: add new name and value to nvtab */
int addname(Nameval newname)
{
	Nameval *nvp;
	int i;

	if (nvtab.nameval == NULL) { /* first time */
		nvtab.nameval =
			(Nameval *) malloc(NVINIT * sizeof(Nameval));
		if (nvtab.nameval == NULL)
			return -1;
		nvtab.max = NVINIT;
		nvtab.nval = 0;
	} else if (nvtab.nval >= nvtab.max) { /* grow */
		nvp = (Nameval *) realloc(nvtab.nameval,
			(NVGROW*nvtab.max) * sizeof(Nameval));
		if (nvp == NULL)
			return -1;
		nvtab.max *= NVGROW;
		nvtab.nameval = nvp;
	}
	for (i = 0; i < nvtab.nval && nvtab.nameval[i].name != NULL; i++)
		;
	nvtab.nameval[i] = newname;
	return nvtab.nval++;
}

/* delname: remove first matching nameval from nvtab */
int delname(char *name)
{
	int i;

	for (i = 0; i < nvtab.nval; i++)
		if (nvtab.nameval[i].name != NULL &&
		    strcmp(nvtab.nameval[i].name, name) == 0) {
			nvtab.nameval[i].name = NULL;
			nvtab.nameval[i].value = 0;
			nvtab.nval--;
			return 1;
		}
	return 0;
}

void printnvtab(void)
{
	int i, count;

	printf("{");
	count = 0;
	for (i = 0; i < nvtab.max; i++) {
		if (i == 0)
			printf(" ");
		else
			printf(", ");
		if (count >= nvtab.nval || nvtab.nameval[i].name == NULL) {
			printf("NULL");
		} else {
			printf("\"%s\" -> %d", nvtab.nameval[i].name,
				nvtab.nameval[i].value);
			count++;
		}
	}
	printf(" }\n");
}

int main(int argc, char *argv[])
{
	struct Nameval nv;

	nv.name = "a";
	nv.value = 100;
	addname(nv);
	nv.name = "b";
	nv.value = 200;
	addname(nv);
	nv.name = "b";
	nv.value = 250;
	addname(nv);
	nv.name = "c";
	nv.value = 300;
	addname(nv);
	delname("b");
	delname("c");
	nv.name = "d";
	nv.value = 400;
	addname(nv);
	delname("d");

	printnvtab();

	return 0;
}

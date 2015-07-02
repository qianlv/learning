#include <stdio.h>

struct re_atom;
struct re_atom *compile(char*);
void	freeregexp(struct re_atom*);
int	match(struct re_atom*, char*, int*, int*);

int main(int argc, char *argv[])
{
	struct re_atom *regexp;
	int m, start, end;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <re> <str>\n", argv[0]);
		return 1;
	}
	regexp = compile(argv[1]);
	if (regexp == NULL) {
		fprintf(stderr, "can't compile regular expression\n");
		return 2;
	}
	m = match(regexp, argv[2], &start, &end);
	freeregexp(regexp);

	if (m)
		return 0;
	else
		return 1;
}

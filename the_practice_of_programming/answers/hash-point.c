#include <stdio.h>
#include <math.h>

struct point {
	int x;
	int y;
};

struct point_float {
	float x;
	float y;
};

struct point_polar {
	int r;
	int theta;
};

struct point_3d {
	int x;
	int y;
	int z;
};

enum { NHASH = 17, MULTIPLIER = 31 };

int hash_point(const struct point *p)
{
	return (unsigned int) (((p->x * MULTIPLIER) + p->y) * MULTIPLIER) % NHASH;
}

int hash_point_polar(const struct point_polar *p)
{
	return (unsigned int) (((p->r * MULTIPLIER) + p->theta) * MULTIPLIER) % NHASH;
}

int hash_point_float(const struct point_float *p)
{
	return (unsigned int) (((p->x * MULTIPLIER) + p->y) * MULTIPLIER) % NHASH;
}

int hash_point_3d(const struct point_3d *p)
{
	return (unsigned int) ((((p->x * MULTIPLIER) + p->y) * MULTIPLIER + p->z) * MULTIPLIER) % NHASH;
}

static void clear_array(int array[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		array[i] = 0;
}

static void print_histogram(int array[], int n)
{
	int i, j;
	int num_width;

	num_width = snprintf(NULL, 0, "%d", n);
	for (i = 0; i < n; i++) {
		printf("%*d:", num_width, i);
		for (j = 0; j < array[i]; j++)
			printf("#");
		printf(" %d\n", j);
	}
}

int main(int argc, char *argv[])
{
	int pseudo_hash[NHASH];
	int x, y, z;

	clear_array(pseudo_hash, NHASH);
	for (x = -5; x <= 5; x++) {
		for (y = -5; y <= 5; y++) {
			struct point p;
			p.x = x;
			p.y = y;
			pseudo_hash[hash_point(&p)]++;
		}
	}
	printf("2D integer\n");
	print_histogram(pseudo_hash, NHASH);

	printf("\n");

	clear_array(pseudo_hash, NHASH);
	for (x = -5; x <= 5; x++) {
		for (y = -5; y <= 5; y++) {
			struct point_polar p;
			p.r = sqrt(x * x + y * y);
			p.theta = atan2(y, x);
			pseudo_hash[hash_point_polar(&p)]++;
		}
	}
	printf("2D integer polar\n");
	print_histogram(pseudo_hash, NHASH);
	printf("\n");

	clear_array(pseudo_hash, NHASH);
	for (x = -4; x <= 4; x++) {
		for (y = -4; y <= 4; y++) {
			for (z = -4; z <= 4; z++) {
				struct point_3d p;
				p.x = x;
				p.y = y;
				p.z = z;
				pseudo_hash[hash_point_3d(&p)]++;
			}
		}
	}
	printf("3D integer\n");
	print_histogram(pseudo_hash, NHASH);

	printf("\n");

	clear_array(pseudo_hash, NHASH);
	for (x = -5; x <= 5; x++) {
		for (y = -5; y <= 5; y++) {
			struct point_float p;
			p.x = cos(x);
			p.y = tan(y);
			pseudo_hash[hash_point_float(&p)]++;
		}
	}
	printf("2D float\n");
	print_histogram(pseudo_hash, NHASH);

	printf("\n");

	clear_array(pseudo_hash, NHASH);
	for (x = -5; x <= 5; x++) {
		for (y = -5; y <= 5; y++) {
			struct point_float p;
			p.x = x / 100.0;
			p.y = y / 100.0;
			pseudo_hash[hash_point_float(&p)]++;
		}
	}
	printf("2D float, closely spaced\n");
	print_histogram(pseudo_hash, NHASH);

	printf("\n");

	clear_array(pseudo_hash, NHASH);
	for (x = -5; x <= 5; x++) {
		for (y = -5; y <= 5; y++) {
			struct point_float p;
			p.x = x / 1000.0;
			p.y = y / 1000.0;
			pseudo_hash[hash_point_float(&p)]++;
		}
	}
	printf("2D float, very closely spaced\n");
	print_histogram(pseudo_hash, NHASH);

	return 0;
}

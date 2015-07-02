#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SCRATCH_FILENAME "op-cost.scratch"

enum { NUM_ITERATIONS = 5000000 };

static double cal;

static double nanos(clock_t start, clock_t end)
{
	return ((double) end - start) / CLOCKS_PER_SEC * 1000000 / NUM_ITERATIONS;
}

/* calibrate the timer by timing an empty loop */
/* result is in nanoseconds */
static void calibrate(void)
{
	clock_t start, end;
	int i;

	start = clock();
	for (i = 0; i < NUM_ITERATIONS; i++)
		;
	end = clock();
	cal = nanos(start, end);
}

#define TIME_SETUP(pre, expr, post) \
{ \
	int _i; \
	clock_t start, end; \
	{ pre; } \
	start = clock(); \
	for (_i = 0; _i < NUM_ITERATIONS; _i++) { \
		expr; \
	} \
	end = clock(); \
	{ post; } \
	printf("  %-30s %9.6f\n", #expr, nanos(start, end) - cal); \
}

#define TIME(expr) TIME_SETUP(, expr, )

static int sum1(int i1)
{
	return i1;
}

static int sum2(int i1, int i2)
{
	return i1 + i2;
}

static int sum3(int i1, int i2, int i3)
{
	return i1 + i2 + i3;
}

int main(void)
{
	int i, i1 = 1, i2 = 2, i3 = 3, i4 = 4;
	float f1 = 1.1, f2 = 10.0, f3 = 2.3;
	double d1 = 2.2, d2 = 3.3, d3 = 1.4;
	FILE *fp;
	int v[10] = { 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	char s[20];

	calibrate();
	printf("Calibration: %.6f\n", cal);

	printf("\n");
	printf("Int Operations\n");
	TIME(i1++)
	TIME(i1 = i2 + i3)
	TIME(i1 = i2 - i3)
	TIME(i1 = i2 * i3)
	TIME(i1 = i2 / i3)
	TIME(i1 = i2 % i3)

	printf("\n");
	printf("Float Operations\n");
	TIME(f1 = f2)
	TIME(f1 = f2 + f3)
	TIME(f1 = f2 - f3)
	TIME(f1 = f2 * f3)
	TIME(f1 = f2 / f3)

	printf("\n");
	printf("Double Operations\n");
	TIME(d1 = d2)
	TIME(d1 = d2 + d3)
	TIME(d1 = d2 - d3)
	TIME(d1 = d2 * d3)
	TIME(d1 = d2 / d3)

	printf("\n");
	printf("Numeric Conversions\n");
	TIME(i1 = f1)
	TIME(f1 = i1)

	printf("\n");
	printf("Integer Vector Operations\n");
	i = 4;
	TIME(v[i] = i)
	TIME(v[v[i]] = i)
	TIME(v[v[v[i]]] = i)

	printf("\n");
	printf("Control Structures\n");
	TIME(if (i == 5) i1++)
	TIME(if (i != 5) i1++)
	TIME(while (i < 0) i1++)
	TIME(i1 = sum1(i2))
	TIME(i1 = sum2(i2, i3))
	TIME(i1 = sum3(i2, i3, i4))

	printf("\n");
	printf("Input/Output\n");
	TIME_SETUP(fp = fopen(SCRATCH_FILENAME, "w"), fputs(s, fp), fclose(fp))
	TIME_SETUP(fp = fopen(SCRATCH_FILENAME, "r"), fgets(s, 9, fp), fclose(fp))
	TIME_SETUP(fp = fopen(SCRATCH_FILENAME, "w"), fprintf(fp, "%d\n", i), fclose(fp))
	TIME_SETUP(fp = fopen(SCRATCH_FILENAME, "r"), fscanf(fp, "%d", &i1), fclose(fp))
	unlink(SCRATCH_FILENAME);

	printf("\n");
	printf("Malloc\n");
	TIME(free(malloc(8)))

	printf("\n");
	printf("String Functions\n");
	TIME(strcpy(s, "0123456789"))
	TIME(i1 = strcmp(s, s))
	TIME(i1 = strcmp(s, "a123456789"))

	printf("\n");
	printf("String/Number Conversions\n");
	TIME(i1 = atoi("12345"))
	TIME(sscanf("12345", "%d", &i1))
	TIME(sprintf(s, "%d", i))
	TIME(f1 = atof("123.45"))
	TIME(sscanf("123.45", "%f", &f1))
	TIME(sprintf(s, "%6.2f", 123.45))

	printf("\n");
	printf("Math Functions\n");
	TIME(i1 = rand())
	TIME(f1 = log(f2))
	TIME(f1 = exp(f2))
	TIME(f1 = sin(f2))
	TIME(f1 = sqrt(f2))

	return 0;
}

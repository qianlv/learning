#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <list>
#include <vector>

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
	printf("  %-36s %9.6f\n", #expr, nanos(start, end) - cal); \
}

#define TIME(expr) TIME_SETUP(, expr, )

class a_class {
public:
	virtual ~a_class() {
	}
	void fn() {
	}
	virtual void vfn() {
	}
	inline void ifn() {
	}
};

class b_class : public a_class {
public:
	virtual ~b_class() {
	}
	virtual void vfn() {
	}
};

int main(void)
{
	calibrate();
	printf("Calibration: %.6f\n", cal);

	a_class a, a1, *ap;
	b_class b;

	printf("\n");
	printf("Object Operations\n");
	TIME(delete(new a_class))
	TIME(delete(new b_class))
	TIME(a1 = a)
	TIME(a = b)

	printf("\n");
	printf("Member Function Calls\n");
	TIME(a.fn())
	TIME(a.vfn())
	TIME(a.ifn())
	ap = &b;
	TIME(ap->fn())
	TIME(ap->vfn())
	TIME(ap->ifn())

	printf("\n");
	printf("STL\n");
	std::vector<int> v(10), *vp;
	TIME(delete(new std::vector<int>))
	TIME(delete(new std::vector<int>(10)))
	TIME_SETUP(vp = new std::vector<int>, vp->reserve(100), delete vp)
	TIME(v.size())
	std::list<int> l(10);
	TIME(delete(new std::list<int>))
	TIME(delete(new std::list<int>(10)))
	TIME(l.size())

	return 0;
}

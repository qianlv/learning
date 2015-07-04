/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 6-4 */

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "eprintf.h"

typedef union {
	unsigned char c;
	unsigned int i;
	float f;
} data_type;

enum { NHASH = 1023, HASHMUL = 13 };

/* we keep data counts in a hash table */
struct count_node {
	int type;
	data_type v;
	unsigned long count;
	struct count_node *next;
};

struct count_node *count[NHASH];

static int cmp_c(data_type a, data_type b)
{
	return a.c - b.c;
}

static int cmp_i(data_type a, data_type b)
{
	if (a.i > b.i)
		return 1;
	else if (a.i < b.i)
		return -1;
	else
		return 0;
}

static int cmp_f(data_type a, data_type b)
{
	if (a.f > b.f)
		return 1;
	else if (a.f < b.f)
		return -1;
	else
		return 0;
}

static size_t read_c(data_type *v, FILE *fp)
{
	return fread(v, sizeof(v->c), 1, fp);
}

static size_t read_i(data_type *v, FILE *fp)
{
	return fread(v, sizeof(v->i), 1, fp);
}

static size_t read_f(data_type *v, FILE *fp)
{
	return fread(v, sizeof(v->f), 1, fp);
}

static unsigned int hash_generic(void *p, size_t len)
{
	unsigned int h;
	int i;

	h = 0;
	for (i = 0; i < len; i++)
		h = HASHMUL * h + ((char *) p)[i];

	return h % NHASH;
}

static unsigned int hash_c(data_type v)
{
	return hash_generic(&v, sizeof(v.c));
}

static unsigned int hash_i(data_type v)
{
	return hash_generic(&v, sizeof(v.i));
}

static unsigned int hash_f(data_type v)
{
	return hash_generic(&v, sizeof(v.f));
}

static const char *tostring_c(data_type v)
{
	static char buf[32];

	snprintf(buf, sizeof(buf), "%.2x  %c",
		v.c, isprint(v.c) ? v.c : '-');

	return buf;
}

static const char *tostring_i(data_type v)
{
	static char buf[sizeof(v.i) * 2 + 1];

	snprintf(buf, sizeof(buf), "%08X", v.i);

	return buf;
}

static const char *tostring_f(data_type v)
{
	static char buf[32];

	snprintf(buf, sizeof(buf), "%g", v.f);

	return buf;
}

/* the types handled by this program */
/* must be kept in sync with type_functions */
enum TYPES {
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	NUM_TYPES
};

/* dispatch functions for the various data types */
struct {
	size_t (*read)(data_type *, FILE *);
	int (*cmp)(data_type, data_type);
	unsigned int (*hash)(data_type);
	const char *(*tostring)(data_type);
} type_functions[] = {
	{ read_c, cmp_c, hash_c, tostring_c },
	{ read_i, cmp_i, hash_i, tostring_i },
	{ read_f, cmp_f, hash_f, tostring_f },
};

size_t read_dt(int type, data_type *v, FILE *fp)
{
	assert(type >= 0 && type < NUM_TYPES);
	return type_functions[type].read(v, fp);
}

int cmp(int type, data_type a, data_type b)
{
	assert(type >= 0 && type < NUM_TYPES);
	return type_functions[type].cmp(a, b);
}

unsigned int hash(int type, data_type v)
{
	assert(type >= 0 && type < NUM_TYPES);
	return type_functions[type].hash(v);
}

const char *tostring(int type, data_type v)
{
	assert(type >= 0 && type < NUM_TYPES);
	return type_functions[type].tostring(v);
}

/* newnode:  create a new hash table node */
static struct count_node *newnode(void)
{
	struct count_node *p;

	p = emalloc(sizeof(struct count_node));
	p->count = 0;
	p->next = NULL;

	return p;
}

/* lookup:  find a node by value, creating if necessary */
static struct count_node *lookup(int type, data_type v)
{
	unsigned int h;
	struct count_node *p;

	h = hash(type, v);
	for (p = count[h]; p != NULL; p = p->next) {
		if (cmp(type, p->v, v) == 0)
			return p;
	}
	p = newnode();
	p->type = type;
	p->v = v;
	p->next = count[h];
	count[h] = p;

	return p;
}

/* increment:  increment the count for a data value */
static void increment(int type, data_type v)
{
	struct count_node *p;

	p = lookup(type, v);
	p->count++;
}

static void hash_free(void)
{
	struct count_node *p, *next;
	int i;

	for (i = 0; i < NHASH; i++) {
		for (p = count[i]; p != NULL; p = next) {
			next = p->next;
			free(p);
		}
	}
}

static int count_node_cmp(const void *a, const void *b)
{
	const struct count_node *an, *bn;

	an = *(const struct count_node **) a;
	bn = *(const struct count_node **) b;
	if (an->type < bn->type)
		return -1;
	else if (an->type > bn->type)
		return 1;
	return cmp(an->type, an->v, bn->v);
}

/* hash_values_sorted:  get an array of hash table nodes in sorted order */
struct count_node **hash_values_sorted(int *len)
{
	struct count_node *p, **a;
	int i, n;

	n = 0;
	for (i = 0; i < NHASH; i++) {
		for (p = count[i]; p != NULL; p = p->next)
			n++;
	}
	a = emalloc(n * sizeof(struct count_node));
	n = 0;
	for (i = 0; i < NHASH; i++) {
		for (p = count[i]; p != NULL; p = p->next)
			a[n++] = p;
	}
	qsort(a, n, sizeof(struct count_node *), count_node_cmp);
	*len = n;

	return a;
}

/* freq main: display data frequency counts */
int main(int argc, char *argv[])
{
	struct count_node *p;
	int i, o, len;
	data_type v;
	struct count_node **values;
	int type = TYPE_CHAR;

	setprogname("freq");
	while ((o = getopt(argc, argv, "ht:")) != -1) {
		switch (o) {
			case 'h':
				printf("usage: freq [-t char|int|float]\n");
				exit(0);
				break;
			case 't':
				if (strcmp(optarg, "char") == 0)
					type = TYPE_CHAR;
				else if (strcmp(optarg, "int") == 0)
					type = TYPE_INT;
				else if (strcmp(optarg, "float") == 0)
					type = TYPE_FLOAT;
				else
					eprintf("Unknown data type \"%s\".", optarg);
				break;
			case '?':
			default:
				exit(1);
				break;
		}
	}

	while (read_dt(type, &v, stdin) != 0)
		increment(type, v);

	values = hash_values_sorted(&len);
	for (i = 0; i < len; i++) {
		p = values[i];
		if (p->count != 0)
			printf("%s  %lu\n", tostring(type, p->v), p->count);
	}
	free(values);

	hash_free();

	return 0;
}

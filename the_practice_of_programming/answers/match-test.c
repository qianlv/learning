/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercises 9-6 and 9-7 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "timer.h"

int	match(char*, char*);
int	matchhere(char*, char*);
int	matchhere_iter(char*, char*);
int	matchstar(int, char*, char*);

static const int ITERATION_CHUNK = 10000;

/* leaves matches per second in the variable mps */
#define TIME(op) { \
	double _t; \
	long _n; \
	timer_start(); \
	do { \
		int _i; \
		for (_i = 0; _i < ITERATION_CHUNK; _i++) { \
			op; \
		} \
		_n += ITERATION_CHUNK; \
	} while ((_t = timer_elapsed()) < 1.0); \
	mps = _n / _t; \
}

#define NELEMS(a) (sizeof(a) / sizeof(a[0]))

/* test the performance of match versus strstr (exercise 9-6) */
void test_match_strstr(void)
{
	char *needles[] = {
		"",
		"abc",
		"xyz",
		"abc%%%%%%%%%%",
	};
	char *haystacks[] = {
		"",
		"abc",
		"abc%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
		"%%%%%%%%%%%%%%%%%%%%%abc%%%%%%%%%%%%%%%%%%%%%",
		"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%abc",

	};
	int i, j;

	for (j = 0; j < NELEMS(haystacks); j++) {
		for (i = 0; i < NELEMS(needles); i++) {
			double mps, match_mps, strstr_mps;

			printf("\"%s\" in \"%s\"\n", needles[i], haystacks[j]);
			assert(match(needles[i], haystacks[j])
			       == (strstr(haystacks[j], needles[i]) != NULL));
			TIME(match(needles[i], haystacks[j]))
			match_mps = mps;
			TIME(strstr(haystacks[j], needles[i]))
			strstr_mps = mps;
			printf("match / strstr = %.f / %.f = %.4f\n",
				match_mps, strstr_mps, match_mps / strstr_mps);
		}
	}
}

/* test the performance of recursive and non-recursivle matchhere (exercise 9-7) */
void test_matchhere_iter(void)
{
	char *regexps[] = {
		"",
		"abc",
		"abc$",
		"a*b*c*d",
		"..................",
	};
	char *texts[] = {
		"",
		"abc%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
		"%%%%%%%%%%%%%%%%%%%%%abc%%%%%%%%%%%%%%%%%%%%%",
	};
	int i, j;

	for (j = 0; j < NELEMS(regexps); j++) {
		for (i = 0; i < NELEMS(texts); i++) {
			double mps, matchhere_mps, matchhere_iter_mps;

			printf("\"%s\" in \"%s\"\n", regexps[j], texts[i]);
			assert(matchhere(regexps[j], texts[i])
			       == matchhere_iter(regexps[j], texts[i]));
			TIME(matchhere(regexps[j], texts[i]))
			matchhere_mps = mps;
			TIME(matchhere_iter(regexps[j], texts[i]))
			matchhere_iter_mps = mps;
			printf("matchhere / matchhere_iter = %.f / %.f = %.4f\n",
				matchhere_mps, matchhere_iter_mps,
				matchhere_mps / matchhere_iter_mps);
		}
	}
}

int main(void)
{
	test_match_strstr();
	printf("\n");
	test_matchhere_iter();

	return 0;
}

/* matchhere: search for regexp at beginning of text */
int matchhere(char *regexp, char *text)
{
	if (regexp[0] == '\0')
		return 1;
	if (regexp[1] == '*')
		return matchstar(regexp[0], regexp+2, text);
	if (regexp[0] == '$' && regexp[1] == '\0')
		return *text == '\0';
	if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
		return matchhere(regexp+1, text+1);
	return 0;
}

/* matchhere_iter: search for regexp at beginning of text (non-recursively) */
int matchhere_iter(char *regexp, char *text)
{
	for (;;) {
		if (regexp[0] == '\0')
			return 1;
		if (regexp[1] == '*')
			return matchstar(regexp[0], regexp+2, text);
		if (regexp[0] == '$' && regexp[1] == '\0')
			return *text == '\0';
		if (*text=='\0' || !(regexp[0]=='.' || regexp[0]==*text))
			return 0;
		regexp++;
		text++;
	}
}

/* match: search for regexp anywhere in text */
int match(char *regexp, char *text)
{
	if (regexp[0] == '^')
		return matchhere(regexp+1, text);
	do {	/* must look even if string is empty */
		if (matchhere(regexp, text))
			return 1;
	} while (*text++ != '\0');
	return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int matchstar(int c, char *regexp, char *text)
{
	do {	/* a * matches zero or more instances */
		if (matchhere(regexp, text))
			return 1;
	} while (*text != '\0' && (*text++ == c || c == '.'));
	return 0;
}

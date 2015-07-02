/* Copyright (C) 1999 Lucent Technologies */
/* Based on an excerpt from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 3-6 */

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <vector>

using namespace std;

const int  NPREF = 2;
const int  NHASH = 4093;	// size of state hash table array
const int  MULTIPLIER = 31;	// size of state hash table array
const char NONWORD[] = "\n";	// cannot appear as real line: we remove newlines
const int  MAXGEN = 10000; // maximum words generated

struct Prefix {
	string words[NPREF];

	Prefix()
	{
		for (int i = 0; i < NPREF; i++)
			words[i] = NONWORD;
	}

	void advance(const string& s)
	{
		int i;

		for (i = 0; i < NPREF - 1; i++)
			words[i] = words[i + 1];
		words[i] = s;
	}

	unsigned int hash()
	{
		unsigned int h;

		h = 0;
		for (int i = 0; i < NPREF; i++) {
			for (unsigned int j = 0; j < words[i].size(); j++)
				h = h * MULTIPLIER + words[i][j];
		}

		return h;
	}

	bool operator==(const Prefix& other)
	{
		for (int i = 0; i < NPREF; i++)
			if (words[i] != other.words[i])
				return false;
		return true;
	}
};

struct Suffix {
	string word;
	Suffix *next;

	Suffix(const string &s)
	{
		word = s;
		next = NULL;
	}
};

struct State {
	Prefix pref;
	Suffix *suf;
	State *next;

	State()
	{
		suf = NULL;
		next = NULL;
	}

	~State()
	{
		Suffix *p, *next;

		for (p = suf; p != NULL; p = next) {
			next = p->next;
			delete p;
		}
	}

	void add_suffix(const string& s)
	{
		Suffix *p;

		p = new Suffix(s);
		p->next = suf;
		suf = p;
	}
};

State *statetab[NHASH];

void		build(Prefix&, istream&);
void		generate(int nwords);
void		add(Prefix&, const string&);

// markov main: markov-chain random text generation
int main(void)
{
	int	nwords = MAXGEN;
	Prefix prefix;	// current input prefix

	// srand(time(NULL));
	srand(0);
	build(prefix, cin);
	add(prefix, NONWORD);
	generate(nwords);
	return 0;
}

// build: read input words, build state table
void build(Prefix& prefix, istream& in)
{
	string buf;

	while (in >> buf)
		add(prefix, buf);
}

// add: add word to suffix deque, update prefix
void add(Prefix& prefix, const string& s)
{
	State *sp;
	unsigned int h;

	h = prefix.hash() % NHASH;
	for (sp = statetab[h]; sp != NULL; sp = sp->next) {
		if (sp->pref == prefix)
			break;
	}
	if (sp == NULL) {
		sp = new State();
		sp->pref = prefix;
		sp->next = statetab[h];
		statetab[h] = sp;
	}
	sp->add_suffix(s);
	prefix.advance(s);
}

// generate: produce output, one word per line
void generate(int nwords)
{
	State *sp;
	Suffix *suf;
	Prefix prefix;
	string w;
	unsigned int h;
	int i, nmatch;

	for (i = 0; i < nwords; i++) {
		h = prefix.hash() % NHASH;
		for (sp = statetab[h]; sp != NULL; sp = sp->next) {
			if (sp->pref == prefix)
				break;
		}
		nmatch = 0;
		for (suf = sp->suf; suf != NULL; suf = suf->next) {
			if (rand() % ++nmatch == 0) /* prob = 1/nmatch */
				w = suf->word;
		}
		if (w == NONWORD)
			break;
		cout << w << "\n";
		prefix.advance(w);
	}
}

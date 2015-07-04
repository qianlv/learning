/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 3-5 */

// Types modifiable at compile time. Try for example
// g++ -DQUEUE_TYPE_ARRAY markov++.c

// QUEUE_TYPE is the type of a prefix
#if !defined(QUEUE_TYPE_DEQUE) && !defined(QUEUE_TYPE_LIST) && \
    !defined(QUEUE_TYPE_VECTOR) && !defined(QUEUE_TYPE_ARRAY)
#define QUEUE_TYPE_DEQUE
#endif
// LIST_TYPE is the type of a suffix list
#if !defined(LIST_TYPE_VECTOR) && !defined(LIST_TYPE_LIST)
#define LIST_TYPE_VECTOR
#endif

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <list>

using namespace std;

const int  NPREF = 2;
const char NONWORD[] = "\n";	// cannot appear as real line: we remove newlines
const int  MAXGEN = 10000; // maximum words generated

#if defined(QUEUE_TYPE_DEQUE)
typedef deque<string> Prefix;
#elif defined(QUEUE_TYPE_LIST)
typedef list<string> Prefix;
#elif defined(QUEUE_TYPE_VECTOR)
typedef vector<string> Prefix;
#elif defined(QUEUE_TYPE_ARRAY)
typedef string Prefix[NPREF];
int prefix_length = 0;
#endif

// prefixcomp: return true if a < b. This is necessary only with
// QUEUE_TYPE_ARRAY, but is easily defined for the other cases.
struct prefixcomp
{
	bool operator()(const Prefix& a, const Prefix& b) const
	{
#if defined(QUEUE_TYPE_DEQUE) || defined(QUEUE_TYPE_LIST) || \
    defined(QUEUE_TYPE_VECTOR)
		return a < b;
#elif defined(QUEUE_TYPE_ARRAY)
		int i;
		for (i = 0; i < NPREF; i++) {
			if (a[i] < b[i])
				return true;
			if (a[i] > b[i])
				return false;
		}
		return false;
#endif
	}
};

#if defined(LIST_TYPE_VECTOR)
map<Prefix, vector<string>, prefixcomp> statetab; // prefix -> suffixes
#elif defined(LIST_TYPE_LIST)
map<Prefix, list<string>, prefixcomp> statetab; // prefix -> suffixes
#endif

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
	for (int i = 0; i < NPREF; i++)
		add(prefix, NONWORD);
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

// add: add word to suffix list, update prefix
void add(Prefix& prefix, const string& s)
{
#if defined(QUEUE_TYPE_DEQUE) || defined(QUEUE_TYPE_LIST)
	if (prefix.size() == NPREF) {
		statetab[prefix].push_back(s);
		prefix.pop_front();
	}
	prefix.push_back(s);
#elif defined(QUEUE_TYPE_VECTOR)
	if (prefix.size() == NPREF) {
		statetab[prefix].push_back(s);
		prefix.erase(prefix.begin());
	}
	prefix.push_back(s);
#elif defined(QUEUE_TYPE_ARRAY)
	if (prefix_length == NPREF) {
		statetab[prefix].push_back(s);
		for (int i = 0; i < NPREF - 1; i++)
			prefix[i] = prefix[i + 1];
		prefix[NPREF - 1] = s;
	} else {
		prefix[prefix_length++] = s;
	}
#endif
}

// generate: produce output, one word per line
void generate(int nwords)
{
	Prefix prefix;
	int i;

#if defined(QUEUE_TYPE_ARRAY)
	prefix_length = 0;
#endif

	for (i = 0; i < NPREF; i++)
		add(prefix, NONWORD);
	for (i = 0; i < nwords; i++) {
		string w;
#if defined(LIST_TYPE_VECTOR)
		vector<string>& suf = statetab[prefix];
		w = suf[rand() % suf.size()];
#elif defined(LIST_TYPE_LIST)
		list<string>& suf = statetab[prefix];
		int nmatch = 0;
		for (list<string>::iterator sp = suf.begin(); sp != suf.end(); sp++)
			if (rand() % ++nmatch == 0) /* prob = 1/nmatch */
				w = *sp;
#endif
		if (w == NONWORD)
			break;
		cout << w << "\n";
#if defined(QUEUE_TYPE_DEQUE) || defined(QUEUE_TYPE_LIST)
		prefix.pop_front();	// advance
		prefix.push_back(w);
#elif defined(QUEUE_TYPE_VECTOR)
		prefix.erase(prefix.begin());
		prefix.push_back(w);
#elif defined(QUEUE_TYPE_ARRAY)
		for (int j = 0; j < NPREF - 1; j++)
			prefix[j] = prefix[j + 1];
		prefix[NPREF - 1] = w;
#endif
	}
}

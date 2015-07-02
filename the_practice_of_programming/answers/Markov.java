/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 3-4 */

import java.io.*;
import java.util.*;

class Chain {
	static final int NPREF = 2;	// size of prefix
	static final String NONWORD = "\n";
					// "word" that can't appear
	Hashtable statetab = new Hashtable(); 
					// key = Prefix, value = suffix Vector
	Prefix prefix = new Prefix(NPREF, NONWORD);
					// initial prefix
	Random rand = new Random();

// Chain build: build State table from input stream
void build(InputStream in) throws IOException
{
	StreamTokenizer st = new StreamTokenizer(in);
		
	st.resetSyntax();                     // remove default rules
	st.wordChars(0, Character.MAX_VALUE); // turn on all chars
	st.whitespaceChars(0, ' ');           // except up to blank
	while (st.nextToken() != st.TT_EOF)
		add(st.sval);
	add(NONWORD);
}

// Chain add: add word to suffix list, update prefix
void add(String word)
{
	int i;

	Vector suf = (Vector) statetab.get(prefix);
	if (suf == null) {
		suf = new Vector();
		statetab.put(new Prefix(prefix), suf);
	}
	suf.addElement(word);
	for (i = 0; i < prefix.pref.length - 1; i++)
		prefix.pref[i] = prefix.pref[i + 1];
	prefix.pref[i] = word;
}

// Chain generate: generate output words
void generate(int nwords)
{
	prefix = new Prefix(NPREF, NONWORD);
	for (int i = 0; i < nwords; i++) {
		Vector s = (Vector) statetab.get(prefix);
		if (s == null) {
			System.err.println("Markov: internal error: no state");
			System.exit(1);
		}
		int r = Math.abs(rand.nextInt()) % s.size();
		String suf = (String) s.elementAt(r);
		if (suf.equals(NONWORD))
			break;
		System.out.println(suf);
		int j;
		for (j = 0; j < prefix.pref.length - 1; j++)
			prefix.pref[j] = prefix.pref[j + 1];
		prefix.pref[j] = suf;
	}
}
}

class Prefix {
	public String[] pref;	// NPREF adjacent words from input
static final int MULTIPLIER = 31;	// for hashCode()

// Prefix constructor: duplicate existing prefix
Prefix(Prefix p)
{
	pref = (String[]) p.pref.clone();
}

// Prefix constructor: n copies of str
Prefix(int n, String str)
{
	pref = new String[n];
	for (int i = 0; i < n; i++)
		pref[i] = str;
}

// Prefix hashCode: generate hash from all prefix words
public int hashCode()
{
	int h = 0;

	for (int i = 0; i < pref.length; i++)
		h = MULTIPLIER * h + pref[i].hashCode();
	return h;
}

// Prefix equals: compare two prefixes for equal words
public boolean equals(Object o)
{
	Prefix p = (Prefix) o;

	for (int i = 0; i < pref.length; i++)
		if (!pref[i].equals(p.pref[i]))
			return false;
	return true;
}

}

class Markov {
	static final int MAXGEN = 10000; // maximum words generated
	public static void main(String[] args) throws IOException
	{
		Chain chain = new Chain();
		int nwords = MAXGEN;

		chain.build(System.in);
		chain.generate(nwords);
	}
}

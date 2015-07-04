/* Copyright (C) 1999 Lucent Technologies */
/* Excerpted from 'The Practice of Programming' */
/* by Brian W. Kernighan and Rob Pike */
/* Modified by David Fifield for exercise 4-6 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

class Csv : public istream_iterator<string> {	// read and parse comma-separated values
	// sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625

  public:
	const string& operator*()
	{
		line = istream_iterator<string>::operator*();
		split();
		return line;
	}

	Csv& operator++()
	{
		istream_iterator<string>::operator++();
		return *this;
	}

	istream_iterator<string> eof;

	Csv(istream& fin = cin, string sep = ",") : 
		istream_iterator<string>(fin), eof(), fin(fin), fieldsep(sep)
	{ }

	string getfield(int n);
	int getnfield() const { return nfield; }

  private:
	istream& fin;			// input file pointer
	string line;			// input line
	vector<string> field;	// field strings
	int nfield;				// number of fields
	string fieldsep;		// separator characters

	int getline(string&);
	int split();
	int advplain(const string& line, string& fld, int);
	int advquoted(const string& line, string& fld, int);
};

// split: split line into fields
int Csv::split()
{
	string fld;
	int i, j;

	nfield = 0;
	if (line.length() == 0)
		return 0;
	i = 0;

	do {
		if (i < line.length() && line[i] == '"')
			j = advquoted(line, fld, ++i);	// skip quote
		else
			j = advplain(line, fld, i);
		if (nfield >= field.size())
			field.push_back(fld);
		else
			field[nfield] = fld;
		nfield++;
		i = j + 1;
	} while (j < line.length());

	return nfield;
}

// advquoted: quoted field; return index of next separator
int Csv::advquoted(const string& s, string& fld, int i)
{
	int j;

	fld = "";
	for (j = i; j < s.length(); j++) {
		if (s[j] == '"' && s[++j] != '"') {
			int k = s.find_first_of(fieldsep, j);
			if (k > s.length())	// no separator found
				k = s.length();
			for (k -= j; k-- > 0; )
				fld += s[j++];
			break;
		}
		fld += s[j];
	}
	return j;
}

// advplain: unquoted field; return index of next separator
int Csv::advplain(const string& s, string& fld, int i)
{
	int j;

	j = s.find_first_of(fieldsep, i); // look for separator
	if (j > s.length())               // none found
		j = s.length();
	fld = string(s, i, j-i);
	return j;
}


// getfield: return n-th field
string Csv::getfield(int n)
{
	if (n < 0 || n >= nfield)
		return "";
	else
		return field[n];
}

// Csvtest main: test Csv class
int main(void)
{
	string line;
	Csv csv;

	for ( ; csv != csv.eof; ++csv) {
		line = *csv;
		cout << "line = `" << line <<"'\n";
		for (int i = 0; i < csv.getnfield(); i++)
			cout << "field[" << i << "] = `"
				 << csv.getfield(i) << "'\n";
	}
	return 0;
}

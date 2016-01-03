/*
 * =====================================================================================
 *
 *       Filename:  generic_algorithm.cpp
 *
 *    Description:  Generic Algorithm
 *
 *        Version:  1.0
 *        Created:  2015年12月28日 21时37分36秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iterator>

#include <algorithm>
#include <numeric>
#include <functional>
using namespace std::placeholders;

#include "generic_algorithm.h"

bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void elimDups(vector<string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = std::unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void biggies(vector<string> &words,
             vector<string>::size_type sz)
{
    elimDups(words);
    std::stable_sort(words.begin(), words.end(),
                     [] (const string &a, const string &b)
                        { return a.size() < b.size(); });
    auto wc = std::find_if(words.begin(),  words.end(),
                    [sz] (const string &a) { return a.size() >= sz; });
    auto count = words.end() - wc;
    cout << count << " " << (count > 1 ? "words" : "word")
         << " of length " << sz << " or longer" << endl;
    std::for_each(wc, words.end(), [] (const string &s) { cout << s << " "; });
    cout << endl;
}

void biggies(vector<string> &words,
             vector<string>::size_type sz,
             ostream &os = cout, char c = ' ')
{
    elimDups(words);
    std::stable_sort(words.begin(), words.end(),
                     [] (const string &a, const string &b)
                        { return a.size() < b.size(); });
    auto wc = std::find_if(words.begin(),  words.end(),
                    [sz] (const string &a) { return a.size() >= sz; });
    auto count = words.end() - wc;
    cout << count << " " << (count > 1 ? "words" : "word")
         << " of length " << sz << " or longer" << endl;
    std::for_each(wc, words.end(), [&os, c] (const string &s) { os << s << c; });
    cout << endl;
}

void biggies_p(vector<string> &words,
             vector<string>::size_type sz)
{
    elimDups(words);
    auto pivot = std::partition(words.begin(), words.end(),
        [sz] (const string &a) { return a.size() >= sz; });
    auto count = pivot - words.begin();
    cout << count << " " << (count > 1 ? "words" : "word")
         << " of length " << sz << " or longer" << endl;
    std::for_each(words.begin(), pivot, [] (const string &s) { cout << s << " "; });
    cout << endl;
}

void biggies_sp(vector<string> &words,
             vector<string>::size_type sz)
{
    elimDups(words);
    auto pivot = std::stable_partition(words.begin(), words.end(),
        [sz] (const string &a) { return a.size() >= sz; });
    auto count = pivot - words.begin();
    cout << count << " " << (count > 1 ? "words" : "word")
         << " of length " << sz << " or longer" << endl;
    std::for_each(words.begin(), pivot, [] (const string &s) { cout << s << " "; });
    cout << endl;
}

bool check_size(const string &s, string::size_type sz)
{
    return s.size() >= sz;
}

void biggies_bp(vector<string> &words,
             vector<string>::size_type sz)
{
    elimDups(words);
    auto pivot = std::stable_partition(words.begin(), words.end(),
                bind(check_size, _1, sz));
    auto count = pivot - words.begin();
    cout << count << " " << (count > 1 ? "words" : "word")
         << " of length " << sz << " or longer" << endl;
    std::for_each(words.begin(), pivot, [] (const string &s) { cout << s << " "; });
    cout << endl;
}


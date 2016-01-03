/*
 * =====================================================================================
 *
 *       Filename:  binding.cpp
 *
 *    Description:  Bind
 *
 *        Version:  1.0
 *        Created:  2016年01月02日 19时50分41秒 CST
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

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>
#include <numeric>
#include <functional>
using namespace std::placeholders;

#include "generic_algorithm.h"

std::ostream &print(std::ostream &os, const string &s, char c)
{
    return os << s << c;
}

int main()
{
    auto check6 = std::bind(check_size, _1, 6);
    string s = "hello world";
    bool b1 = check6(s);
    cout << b1 << endl;

    vector<string> words = {"hello", "one", "two", "three", "four"};
    string::size_type sz = 4;
    auto wc = std::find_if(words.begin(), words.end(),
                    bind(check_size, _1, sz));
    cout << (words.end() - wc) << endl;
    for_each(words.begin(), words.end(),
            bind(print, std::ref(cout), _1, ' '));

    biggies_bp(words, 4);
}

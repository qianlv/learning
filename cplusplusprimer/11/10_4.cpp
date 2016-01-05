/*
 * =====================================================================================
 *
 *       Filename:  10_4.cpp
 *
 *    Description:  10.4
 *
 *        Version:  1.0
 *        Created:  2016年01月03日 17时31分41秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <algorithm>
#include <numeric>

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

//#include <cctype>
//using std::tolower;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <set>
using std::set;


string const& strip(string &str)
{
    std::for_each(str.begin(), str.end(), [] (char &c) { c = tolower(c);});
    str.erase(std::remove_if(str.begin(), str.end(), ispunct), str.end());
    return str;
}

int main()
{
    map<string, size_t> word_count;
    set<string> exclude = {"The", "But", "And", "Or", "An", "A", 
                           "the", "but", "and", "or", "an", "a"};
    string word;
    while (cin >> word)
    {
        word = strip(word);
        if (exclude.find(word) == exclude.end())
            ++word_count[word];
    }
    for (const auto &w : word_count)
    {
        cout << w.first << " occurs " << w.second
             << ((w.second > 1) ? " times" : " time") << endl;
    }
}

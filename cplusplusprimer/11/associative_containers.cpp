/*
 * =====================================================================================
 *
 *       Filename:  associative_containers.cpp
 *
 *    Description:  Associative Containers
 *
 *        Version:  1.0
 *        Created:  2016年01月03日 17时21分30秒 CST
 *       Revision:  none
 *       Compiler:  gcc
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

#include <map>
using std::map;

#include <set>
using std::set;

#include <algorithm>
#include <numeric>

int main()
{
    map<string, size_t> word_count;
    set<string> exclude = {"The", "But", "And", "Or", "An", "A", 
                           "the", "but", "and", "or", "an", "a"};
    string word;
    while (cin >> word)
    {
        if (exclude.find(word) == exclude.end())
            ++word_count[word];
    }
    for (const auto &w : word_count)
    {
        cout << w.first << " occurs" << w.second
             << ((w.second > 1) ? " times" : " time") << endl;
    }
}

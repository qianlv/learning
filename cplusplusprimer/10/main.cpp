/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Main
 *
 *        Version:  1.0
 *        Created:  2016年01月01日 16时32分36秒 CST
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

#include <algorithm>
#include <numeric>

#include "generic_algorithm.h"

int main()
{
    vector<string> sv = {"1", "2", "3", "4"};
    string sum = std::accumulate(sv.begin(), sv.end(), string(""));
    cout << sum << endl;

    vector<string> roster1 = {"1", "2", "3", "4"}, roster2 = {"2", "2", "3", "4", "5"};
    cout << (std::equal(roster1.cbegin(), roster1.cend(), roster2.cbegin()) ? "true" : "false") << endl;

    vector<int> ivec(10, -1);
    std::fill_n(ivec.begin(), 10, 1);
    for (const auto &elem : ivec)
        cout << elem << " ";
    cout << endl;

    vector<int> ivec2;
    auto it = std::back_inserter(ivec2);
    *it = 42;
    std::fill_n(std::back_inserter(ivec2), 10, 0);
    for (const auto &elem : ivec2)
        cout << elem << " ";
    cout << endl;

    vector<string> words;
    string word;
    while (cin >> word)
    {
        words.push_back(word);
    }
    elimDups(words);
    stable_sort(words.begin(), words.end(), isShorter);
    for (const auto &elem : words)
        cout << elem << " ";
    cout << endl;
}

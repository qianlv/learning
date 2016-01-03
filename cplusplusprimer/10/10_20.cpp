/*
 * =====================================================================================
 *
 *       Filename:  10_20.cpp
 *
 *    Description:  10.20
 *
 *        Version:  1.0
 *        Created:  2016年01月02日 14时20分27秒 CST
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

int main()
{
    vector<string> words = {
        "one", "two", "three", "four", "five", "fivefive",
        "vecotr<string> words", "vecotr<string> words"
    };
    size_t sz = 6;
    int cnt = std::count_if(words.cbegin(), words.cend(),
            [sz] (const string &w) { return w.size() >= sz; });
    cout << cnt << endl;
}

/*
 * =====================================================================================
 *
 *       Filename:  10_30_31.cpp
 *
 *    Description:  10.30 10.31
 *
 *        Version:  1.0
 *        Created:  2016年01月03日 13时30分01秒 CST
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
#include <iterator>
using std::istream_iterator;
using std::ostream_iterator;

int main()
{
    istream_iterator<int> in(cin), eof;
    vector<int> vec;
    vector<int> vec2;
    std::copy(in, eof, std::back_inserter(vec));
    std::copy(vec.begin(), vec.end(), std::back_inserter(vec2));

    std::sort(vec.begin(), vec.end());
    std::sort(vec2.begin(), vec2.end());
    std::copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
    std::unique_copy(vec2.begin(), vec2.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

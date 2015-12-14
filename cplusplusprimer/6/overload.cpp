/*
 * =====================================================================================
 *
 *       Filename:  overload.cpp
 *
 *    Description:  Overloaded Functions
 *
 *        Version:  1.0
 *        Created:  2015年12月13日 10时48分58秒 CST
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

#include <iterator>
using std::begin;
using std::end;

void print(const char *cp)
{
    if (cp)
        while (*cp)
            cout << *cp++;
        cout << endl;
}

void print(const int *beg, const int *end)
{
    while (beg != end)
        cout << *beg++ << endl;
}

void print(const int ia[], size_t size)
{
    for (size_t i = 0; i < size; ++i)
        cout << ia[i] << endl;
}

int main()
{
    int j[2] = {0, 1};
    print("Hello World");
    print(j, end(j) - begin(j));
    print(begin(j), end(j));
}

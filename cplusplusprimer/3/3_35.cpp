/*
 * =====================================================================================
 *
 *       Filename:  3_35.cpp
 *
 *    Description:  3.35
 *
 *        Version:  1.0
 *        Created:  2015年12月07日 17时19分27秒 CST
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

int main()
{
    const size_t sz = 10;
    int ia[sz];
    int *pbeg = begin(ia);    
    int *pend = end(ia);
    while (pbeg != pend)
    {
        *pbeg = 0;
        ++pbeg;
    }
    for (int *ptr = begin(ia); ptr != end(ia); ++ptr)
        cout << *ptr << endl;
}

/*
 * =====================================================================================
 *
 *       Filename:  arr.cpp
 *
 *    Description:  array usage
 *
 *        Version:  1.0
 *        Created:  2015年12月07日 11时49分33秒 CST
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

#include <cstddef>

#include <iterator>
using std::begin;
using std::end;

int main()
{

    int ia[] = {0, 1, 2, -3, 4, 5, 6, 7, 8, 9};
    int *beg = begin(ia);
    int *last = end(ia);
    for (; beg != last; ++beg)
        cout << *beg << endl;
    int *pbeg = begin(ia);
    int *pend = end(ia);
    while (pbeg != pend && *pbeg >= 0)
        ++pbeg;
    cout << *pbeg << endl;
    ptrdiff_t n = end(ia) - begin(ia);
    cout << "distance = " << n << endl;

    int *p = &ia[2];
    int j = p[1]; // ia[3]
    int k = p[-2]; // ia[0]
    cout << j << " " << k << endl; 
}

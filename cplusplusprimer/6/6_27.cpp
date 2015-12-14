/*
 * =====================================================================================
 *
 *       Filename:  6_27.cpp
 *
 *    Description:  6.27
 *
 *        Version:  1.0
 *        Created:  2015年12月10日 14时40分34秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <initializer_list>
using std::initializer_list;

int sum(initializer_list<int> il)
{
    int ret = 0;
    for (initializer_list<int>::iterator it = il.begin();
         it != il.end(); ++it)
        ret += *it;
    return ret;
}

int main()
{
    cout << sum({1, 2, 3}) << endl;
}

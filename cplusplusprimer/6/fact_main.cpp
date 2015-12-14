/*
 * =====================================================================================
 *
 *       Filename:  fact_main.cpp
 *
 *    Description:  use fact function.
 *
 *        Version:  1.0
 *        Created:  2015年12月09日 14时20分35秒 CST
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

#include "chapter6.h"

int main()
{
    int n;
    while (cin >> n)
    {
        cout << fact(n) << endl;
    }
}


/*
 * =====================================================================================
 *
 *       Filename:  6_10.cpp
 *
 *    Description:  swap 
 *
 *        Version:  1.0
 *        Created:  2015年12月09日 14时45分08秒 CST
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

void swap(int *p, int *q)
{
    *p = *p ^ *q;
    *q = *p ^ *q;
    *p = *q ^ *p;
}

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        swap(&n, &m);
        cout << n << " " << m << endl;
    }
}

/*
 * =====================================================================================
 *
 *       Filename:  6_12.cpp
 *
 *    Description:  6.12 
 *
 *        Version:  1.0
 *        Created:  2015年12月09日 15时18分40秒 CST
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

void swap_ref(int &p, int &q)
{
    p = p ^ q;
    q = p ^ q;
    p = q ^ p;
}

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        swap_ref(n, m);
        cout << n << " " << m << endl;
    }
}

/*
 * =====================================================================================
 *
 *       Filename:  6_22.cpp
 *
 *    Description:  6.22
 *
 *        Version:  1.0
 *        Created:  2015年12月09日 17时38分28秒 CST
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

void swap_pointer(int *&p, int *&q)
{
    int *tmp = p;
    p = q;
    q = tmp;
}

int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        int *l = &n;
        int *r = &m;
        swap_pointer(l, r);
        cout << *l << " " << *r << endl;
    }

}

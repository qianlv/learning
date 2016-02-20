/*
 * =====================================================================================
 *
 *       Filename:  14_5.cpp
 *
 *    Description:  14.5
 *
 *        Version:  1.0
 *        Created:  2016年02月17日 10时50分03秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "employee.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    Employee p1, p2;
    cin >> p1 >> p2;
    cout << p1 << endl;
    cout << p2 << endl;
    cout << (p1 == p2 ) << endl;
}

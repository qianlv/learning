/*
 * =====================================================================================
 *
 *       Filename:  3_34.cpp
 *
 *    Description:  3.34
 *
 *        Version:  1.0
 *        Created:  2015年12月07日 17时16分36秒 CST
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

int main()
{
    int ia[] = {0, 1, 2, 3, 4};
    int *p1 = &ia[3];
    int *p2 = &ia[4];
    p1 += p2 - p1;
    cout << *p1 << endl;
}

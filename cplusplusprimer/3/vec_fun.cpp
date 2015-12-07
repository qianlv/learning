/*
 * =====================================================================================
 *
 *       Filename:  vec_fun.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月06日 20时17分14秒 CST
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
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto &i : v)
        i *= i;
    for (auto i : v)
        cout << i << " ";
    cout << endl;

    vector<unsigned> socores(10, 0);
    unsigned grade;
    while (cin >> grade)
    {
        if (grade <= 100)
        {
            ++socores[grade/10];
        }
    }

}

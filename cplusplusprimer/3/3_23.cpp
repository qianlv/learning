/*
 * =====================================================================================
 *
 *       Filename:  3_23.cpp
 *
 *    Description:  3.23
 *
 *        Version:  1.0
 *        Created:  2015年12月06日 21时16分34秒 CST
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
    vector<int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (vector<int>::iterator it = ivec.begin();
         it != ivec.end(); ++it)
    {
        *it = (*it) * 2;
        cout << *it << " ";
    }
    cout << endl;
}

/*
 * =====================================================================================
 *
 *       Filename:  3_41.cpp
 *
 *    Description: 3.41 
 *
 *        Version:  1.0
 *        Created:  2015年12月07日 21时05分28秒 CST
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

#include <iterator>
using std::begin;
using std::end;

int main()
{
    int ia[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> ivec(begin(ia), end(ia));
    for (auto it = ivec.begin(); it != ivec.end(); ++it)
    {
        cout << *it << endl;
    }
}

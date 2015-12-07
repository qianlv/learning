/*
 * =====================================================================================
 *
 *       Filename:  3_42.cpp
 *
 *    Description:  3.42 
 *
 *        Version:  1.0
 *        Created:  2015年12月07日 21时07分33秒 CST
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
    vector<int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int ia[10];
    for (size_t i = 0; i < ivec.size(); ++i)
    {
        ia[i] = ivec[i];
    }
    for (auto it = begin(ia); it != end(ia); ++it)
        cout << *it << " ";
    cout << endl;
}


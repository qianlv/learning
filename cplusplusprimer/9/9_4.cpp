/*
 * =====================================================================================
 *
 *       Filename:  9_4.cpp
 *
 *    Description:  9.4
 *
 *        Version:  1.0
 *        Created:  2015年12月21日 20时49分52秒 CST
 *       Revision:  none
 *       Compiler:  g++
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

bool contains_element(vector<int>::const_iterator beg,
    vector<int>::const_iterator end, const int elem)
{
    while (beg != end)
    {
        if (*beg == elem)
        {
            return true;
        }
        ++beg;
    }
    return false;
}

int main()
{
    vector<int> ivec = {1, 2, 40, 3};
    cout << contains_element(ivec.cbegin(), ivec.cend(), 0) << endl;
}

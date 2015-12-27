/*
 * =====================================================================================
 *
 *       Filename:  9_5.cpp
 *
 *    Description:  9.5
 *
 *        Version:  1.0
 *        Created:  2015年12月21日 20时57分14秒 CST
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

vector<int>::const_iterator find_element(vector<int>::const_iterator beg,
    vector<int>::const_iterator end, const int elem)
{
    for (; beg != end; ++beg)
        if (*beg == elem) return beg;
    return end;
}

int main()
{
    vector<int> ivec = {1, 2, 40, 3};
    auto iter = find_element(ivec.begin(), ivec.end(), 0);
    if (iter != ivec.end())
        cout << *iter << endl;
    else
        cout << "Not Find Data" << endl;
}

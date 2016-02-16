/*
 * =====================================================================================
 *
 *       Filename:  13_31.cpp
 *
 *    Description:  13.31
 *
 *        Version:  1.0
 *        Created:  2016年01月11日 16时26分43秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>
using std::sort;
#include <vector>
using std::vector;

#include "hasptr.h"

int main()
{
    HasPtr hp1{ "s" }, hp2{ "a" }, hp3{ "e" };
    cout << " --- " << endl;

    vector<HasPtr> vec{ hp1, hp2, hp3 };
    cout << " --- " << endl;

    sort(vec.begin(), vec.end());
    cout << " --- " << endl;

    for (auto &elem : vec)
        elem.show();
}

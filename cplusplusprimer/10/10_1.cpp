/*
 * =====================================================================================
 *
 *       Filename:  10_1.cpp
 *
 *    Description:  10.1
 *
 *        Version:  1.0
 *        Created:  2015年12月28日 21时29分37秒 CST
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

#include <list>
using std::list;

#include <algorithm>

int main()
{
    vector<int> vec = {1, 2, 3, 1, 2, 3, 10, -1, 1};
    list<int> li = {1, 2, 3, 1, 2, 3, 10, -1, 1};
    int same = std::count(vec.begin(), vec.end(), 1);
    int same1 = std::count(li.begin(), li.end(), 2);
    cout << same << " " << same1 << endl;
}

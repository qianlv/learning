/*
 * =====================================================================================
 *
 *       Filename:  10_3.cpp
 *
 *    Description:  10.3 
 *
 *        Version:  1.0
 *        Created:  2015年12月28日 21时45分06秒 CST
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

#include <algorithm>
#include <numeric>

int main()
{
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << std::accumulate(vec.cbegin(), vec.cend(), 0) << endl;
}

/*
 * =====================================================================================
 *
 *       Filename:  10_4.cpp
 *
 *    Description:  10.4
 *
 *        Version:  1.0
 *        Created:  2015年12月28日 21时46分36秒 CST
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
    vector<double> dvec = {1.1, 1.2, 2, 3, 4};
    cout << std::accumulate(dvec.cbegin(), dvec.cend(), 0) << endl;
    cout << std::accumulate(dvec.cbegin(), dvec.cend(), 0.0) << endl;

}

/*
 * =====================================================================================
 *
 *       Filename:  10_28.cpp
 *
 *    Description:  10.28
 *
 *        Version:  1.0
 *        Created:  2016年01月02日 21时55分47秒 CST
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
#include <numeric>
#include <iterator>

int main()
{
    vector<int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> li1;
    std::copy(ivec.begin(), ivec.end(), std::back_inserter(li1)); 
    list<int> li2;
    std::copy(ivec.begin(), ivec.end(), std::inserter(li2, li2.begin())); 
    list<int> li3;
    std::copy(ivec.begin(), ivec.end(), std::front_inserter(li3)); 
    for_each(li1.begin(), li1.end(), [] (int a) { cout << a << " "; });
    cout << endl;
    for_each(li2.begin(), li2.end(), [] (int a) { cout << a << " "; });
    cout << endl;
    for_each(li3.begin(), li3.end(), [] (int a) { cout << a << " "; });
    cout << endl;

    
}

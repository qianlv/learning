/*
 * =====================================================================================
 *
 *       Filename:  10_21.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年01月02日 14时24分03秒 CST
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

#include <algorithm>
#include <numeric>

int main()
{
    int cnt = 10;
    auto f = [&cnt] () -> bool { --cnt; return cnt == 0;};
    while(!f())
        cout << cnt << endl;
    cout << "End" << endl;
    
}

/*
 * =====================================================================================
 *
 *       Filename:  climbing-stairs-70.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月15日 13时58分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int climbStairs(int n)
    {
        if (n == 1 ) return 1;
        int x = 1, y = 2;
        for (int i = 2; i < n; ++i)
        {
            x = x + y;
            std::swap(x, y);
        }
        return y;
    }
};

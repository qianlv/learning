/*
 * =====================================================================================
 *
 *       Filename:  container-with-most-water-11.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月13日 15时35分48秒
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
    int maxArea(vector<int>& height)
    {
        int i = 0, j = (int)height.size() - 1;
        int res = 0;
        while (i < j)
        {
            res = std::max(res, (j - i) * (std::min(height[i], height[j])));
            if (height[i] > height[j])
                --j;
            else
                ++i;
        }
        return res;
    }
};

/*
 * =====================================================================================
 *
 *       Filename:  maximum-subarray-53.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月14日 16时33分51秒
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
    int maxSubArray(vector<int>& nums)
    {
        int res = INT32_MIN;
        int tmp = 0;
        for (int val : nums)
        {
            tmp += val;
            res = std::max(tmp, res);
            tmp = std::max(tmp, 0);
        }
        return res;
    }
};

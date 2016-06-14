/*
 * =====================================================================================
 *
 *       Filename:  jump-game-II-45.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月14日 10时03分37秒
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
#include <climits>
using namespace std;

class Solution
{
public:
    int jump(vector<int>& nums)
    {
        //dp.assign(nums.size(), INT32_MAX);
        //dp[0] = 0;
        //size_t next = 0;
        //for (size_t i = 0; i < nums.size(); ++i)
        //{
            //for (size_t j = next; j < i + nums[i] + 1 && j < nums.size(); ++j)
                //dp[j] = std::min(dp[j], dp[i] + 1);
            //next = std::max(next, i + nums[i] + 1);
        //}
        //return dp[nums.size() - 1];
        if (nums.size() == 1)
            return 0;
        if (nums[0] >= (int)nums.size() - 1)
            return 1;
        size_t next = 0;
        size_t next_point = 1;
        int step = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (i >= next_point)
            {
                ++step;
                next_point = next;
            }
            if (next_point >= nums.size())
                break;
            next = std::max(next, i + nums[i] + 1);
        }
        return step;
    }

    int jump1(vector<int>& nums)
    {
        size_t next = 0;
        size_t next_point = 1;
        int step = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (i >= next_point)
            {
                ++step;
                next_point = next;
            }
            if (next_point >= nums.size())
                break;
            next = std::max(next, i + nums[i] + 1);
        }
        return step;
    }

    //vector<int> dp;
};
int main(void)
{
    return 0;
}

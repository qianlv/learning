/*
 * =====================================================================================
 *
 *       Filename:  jump-game-55.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月14日 19时28分29秒
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
    bool canJump(vector<int>& nums)
    {
        if (nums.size() == 1)
            return true;
        if (nums[0] >= (int)nums.size() - 1)
            return true;
        size_t next = 0;
        size_t next_point = 1;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (i >= next_point)
            {
                if (next <= next_point)
                    return false;
                next_point = next;
            }
            next = std::max(next, i + nums[i] + 1);
        }
        return true;
    }

};
int main(void)
{
    vector<int> nums{10, 1, 10};
    Solution sol;
    std::cout << sol.canJump(nums) << std::endl;
    return 0;
}

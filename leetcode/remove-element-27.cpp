/*
 * =====================================================================================
 *
 *       Filename:  remove-element-27.cpp
 *
 *    Description:  remove element
 *
 *        Version:  1.0
 *        Created:  2016年06月12日 16时29分50秒
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
using namespace std;

class Solution
{
public:
    int removeElement(vector<int>& nums, int val)
    {
        if (nums.size() == 0)
            return 0;
        int i = 0, j = static_cast<int>(nums.size() - 1);
    
        while (i <= j)
        {
            while (i <= j && nums[i] != val)
                ++i;
            while (j >= 0 && nums[j] == val)
                --j;
            std::cout << i << "|" << j << std::endl;
            if (i < j)
            {
                swap(nums[i], nums[j]);
            }
        }
        return j + 1;
    }
};

int main(void)
{
    vector<int> nums {2, 3, 2, 3, 2};
    Solution sol;
    std::cout << sol.removeElement(nums, 3) << std::endl;
    return 0;
}

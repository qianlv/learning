/*
 * =====================================================================================
 *
 *       Filename:  remove-duplicates-from-sorted-array-26.cpp
 *
 *    Description:  std::unqiue
 *
 *        Version:  1.0
 *        Created:  2016年06月12日 16时10分53秒
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
    int removeDuplicates(vector<int>& nums)
    {
        if (nums.size() <= 1)
        {
            return int(nums.size());
        }
        size_t i = 0;
        for (size_t j = 1; j < nums.size(); ++j)
        {
            if (nums[j] != nums[j-1])
            {
                ++i; nums[i] = nums[j];
            }
        }
        return (int)i + 1;
    }
};

int main(void)
{
    vector<int> nums {1, 1, 2, 2};
    Solution sol;
    std::cout << sol.removeDuplicates(nums) << std::endl;
    return 0;
}

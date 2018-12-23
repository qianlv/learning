/*
 * =====================================================================================
 *
 *       Filename:  find-minimum-in-rotated-sorted-array-II-154.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月14日 15时35分44秒
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
    int findMin(vector<int>& nums)
    {
        int l = 0, r = (int)nums.size() - 1;
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] > nums[r]) l = mid + 1;
            else if (nums[mid] == nums[r]) --r;
            else r = mid;
        }
        return nums[l];
    }
};  

int main(void)
{
    vector<int> nums{5, 4};
    Solution sol;
    std::cout << sol.findMin(nums) << std::endl;
    return 0;
}

/*
 * =====================================================================================
 *
 *       Filename:  search-in-rotated-sorted-array-33.cpp
 *
 *    Description:  二分
 *
 *        Version:  1.0
 *        Created:  2016年06月12日 20时05分21秒
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
    int search(vector<int>& nums, int target)
    {
        int l = 0, r = (int)(nums.size()) - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target)
                return mid;
            if (target > nums[mid])
            {
                if (nums[mid] < nums[l])
                {
                    if (target <= nums[r])
                        l = mid + 1;
                    else
                        r = mid - 1;
                }
                else
                {
                    l = mid + 1;
                }
            }
            else
            {
                //std::cout << "---" << nums[mid] << "|" << nums[l] << std::endl;
                if (nums[mid] < nums[l])
                {
                    r = mid  - 1;
                }
                else
                {
                    if (target < nums[l])
                        l = mid + 1;
                    else
                        r = mid - 1;
                }
            }
        }
        return -1;
    }
};
int main(void)
{
    vector<int> nums {1, 3, 1, 1, 1};
    Solution sol;
    std::cout << sol.search(nums, 3) << std::endl;
    return 0;
}

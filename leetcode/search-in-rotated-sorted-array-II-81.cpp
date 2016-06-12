/*
 * =====================================================================================
 *
 *       Filename:  search-in-rotated-sorted-array-II-81.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月12日 21时52分39秒
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
    bool search(vector<int>& nums, int target)
    {
        int l = 0, r = (int)(nums.size()) - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target)
                return true;
            if (nums[mid] == nums[l] && nums[mid] == nums[r])
            {
                ++l;
                --r;
            }
            else if (target > nums[mid])
            {
                //std::cout << "---" << mid << "|" << l << endl;
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
        return false;
    }
};
int main(void)
{
    vector<int> nums {4, 4, 4, 3, 1, 1};
    // vector<int> nums {1, 1, 3, 1};
    Solution sol;
    std::cout << sol.search(nums, 1) << std::endl;
    return 0;
}

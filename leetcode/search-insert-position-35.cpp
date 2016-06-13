/*
 * =====================================================================================
 *
 *       Filename:  search-insert-position-35.cpp
 *
 *    Description:  二分
 *
 *        Version:  1.0
 *        Created:  2016年06月13日 11时12分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
void output(const std::vector<T>& vec)
{
    std::for_each(vec.begin(), vec.end(),
                [](const T& v) {
                    cout << v << " ";
                });
    cout << endl;
}

class Solution
{
public:
    int searchInsert(vector<int>& nums, int target)
    {
        int l = lower_bound(nums, target);
        return l;
    }

    int lower_bound(vector<int>& nums, int target) /* return first element less or equal target, nums.size() is not found */
    {
        int l = 0, r = (int)nums.size() - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] < target)
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return l;
    }

    int upper_bound(vector<int>& nums, int target) /* return first element greater target, -1 is not found */
    {
        int l = 0, r = (int)nums.size() - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] <= target)
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return l;
    }
};

int main(void)
{
    vector<int> nums {1};
    Solution sol;
    std::cout << sol.searchInsert(nums, 0) << std::endl;
    return 0;
}

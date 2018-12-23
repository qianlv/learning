/*
 * =====================================================================================
 *
 *       Filename:  search-for-a-range-34.cpp
 *
 *    Description:  二分
 *
 *        Version:  1.0
 *        Created:  2016年06月13日 10时03分20秒
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
    vector<int> searchRange(vector<int>& nums, int target)
    {
        int l = lower_bound(nums, target);
        //std::cout << l << std::endl;
        if (l == (int)nums.size() || nums[l] != target)
            return {-1, -1};
        int r = upper_bound(nums, target);
        //std::cout << r << std::endl;
        return {l, r -1};
    }

    int lower_bound(vector<int>& nums, int target) /* return first element greater or equal target, nums.size() is not found */
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
    vector<int> nums {5, 7, 7, 8, 8, 10};
    Solution sol;
    output(sol.searchRange(nums, 10));
    return 0;
}

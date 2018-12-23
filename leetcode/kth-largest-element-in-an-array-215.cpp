/*
 * =====================================================================================
 *
 *       Filename:  kth-largest-element-in-an-array-215.cpp
 *
 *    Description:  :v
 *
 *        Version:  1.0
 *        Created:  2016年06月03日 18时06分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
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
    int findKthLargest(vector<int> nums, int k)
    {
        return findKLargestNums(nums, nums.size() - k + 1, 0, nums.size() - 1);
    }

    int findKLargestNums(vector<int>& nums, int k, int l, int r)
    {
        if (l == r)
            return nums[l];
        swap(nums[(l + r) >> 1], nums[r]);    
        //output(nums);
        int i = l - 1;
        for (int j = l; j < r; ++j)
        {
            if (nums[j] <= nums[r])
            {
                ++i;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i+1], nums[r]);
        if (i + 2 - l == k) return nums[i+1];
        if (i + 2 - l > k) return findKLargestNums(nums, k, l, i);
        else return findKLargestNums(nums, k - (i + 2 - l), i + 2, r); 
    }
};

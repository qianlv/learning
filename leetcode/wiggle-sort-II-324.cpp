/*
 * =====================================================================================
 *
 *       Filename:  wiggle-sort-II-324.cpp
 *
 *    Description:  wiggle sort II
 *
 *        Version:  1.0
 *        Created:  2016年06月03日 11时31分30秒
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
    void wiggleSort(vector<int>& nums)
    {
        if (nums.size() <= 1)
            return;
        int m = (nums.size() + 1) / 2 + 1;
        int mid = findKLargestNums(nums, m, 0, nums.size() - 1);
        std::vector<int> tmp;
        tmp.resize(nums.size());
        int l = 0, r = nums.size() -1;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (nums[i] > nums[mid]) tmp[r--] = nums[i];
            if (nums[i] < nums[mid]) tmp[l++] = nums[i];
        }

        while (l < mid) tmp[l++] = nums[mid];
        while (r >= mid) tmp[r--] = nums[mid];
        //output(tmp);
        //cout << l << "|" << r << endl;
        r = nums.size();
        for (size_t i = 0; i < nums.size(); ++i)
            nums[i] = (i % 2 == 0) ? tmp[--l] : tmp[--r];
    }

    int findKLargestNums(vector<int>& nums, int k, int l, int r)
    {
        if (l == r)
            return l;
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
        if (i + 2 - l == k) return i + 1;
        if (i + 2 - l > k) return findKLargestNums(nums, k, l, i);
        else return findKLargestNums(nums, k - (i + 2 - l), i + 2, r); 
    }
};

int main()
{
    std::vector<int> v {
        1
        //1, 1, 1, 1, 2, 2, 2
         //1,5,1,1,6,4
    };
    Solution sol;
    sol.wiggleSort(v);
    output(v);
}

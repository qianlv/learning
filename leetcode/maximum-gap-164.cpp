/*
 * =====================================================================================
 *
 *       Filename:  maximum-gap-164.cpp
 *
 *    Description:  基数排序
 *
 *        Version:  1.0
 *        Created:  2016年06月02日 14时50分31秒
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
    int maximumGap(vector<int>& nums)
    {
        if (nums.size() <= 1)
            return 0;
        int base = 1;
        for (int i = 0; i < 10; ++i)
        {
            BucketSort(nums, base);
            base *= 10;
        }
        int maxval = -1;
        for (int i = 1; i < (int)nums.size(); ++i)
        {
            maxval = std::max(maxval, nums[i] - nums[i-1]);
        }
        return maxval;
    }

    void BucketSort(vector<int>& nums, int base)
    {
        vector<int> counter(10, 0);
        vector<int> tmp;
        tmp.resize(nums.size());
        std::for_each(nums.begin(), nums.end(), 
                [&] (int v) {
                    ++counter[(v / base) % 10];
                });
        for (size_t i = 1; i < 10; ++i)
            counter[i] += counter[i-1];
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            tmp[counter[(nums[i] / base) % 10] - 1] = nums[i];
            --counter[(nums[i] / base) % 10];
        }
        nums.swap(tmp);
    }
};

int main()
{
    std::vector<int> v{10, 1230, 1, 123, 546, 242, 23532, 2345353};
    Solution sol;
    cout << sol.maximumGap(v) << endl;
}

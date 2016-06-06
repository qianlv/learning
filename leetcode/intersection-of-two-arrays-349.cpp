/*
 * =====================================================================================
 *
 *       Filename:  intersection-of-two-arrays-349.cpp
 *
 *    Description:  intersection of two array
 *
 *        Version:  1.0
 *        Created:  2016年06月06日 10时08分39秒
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
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        std::sort(nums1.begin(), nums1.end());
        auto it1 = std::unique(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        auto it2 = std::unique(nums2.begin(), nums2.end());

        auto it = std::set_intersection(
            nums1.begin(), it1, nums2.begin(), it2, nums1.begin());
        nums1.resize(it - nums1.begin());
        return nums1;
    }
};

int main(void)
{
    std::vector<int> v1{1, 2, 2, 1}, v2{2, 2};
    Solution sol;
    output(sol.intersection(v1, v2));
    return 0;
}

/*
 * =====================================================================================
 *
 *       Filename:  intersection-of-two-350.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月06日 10时25分36秒
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
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
    {
        std::sort(nums1.begin(), nums1.end());
        // auto it1 = std::unique(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        // auto it2 = std::unique(nums2.begin(), nums2.end());

        auto it = std::set_intersection(
            nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), nums1.begin());
        nums1.resize(it - nums1.begin());
        return nums1;
    }
};

int main(void)
{
    std::vector<int> v1{1, 2, 2, 1, 2, 3}, v2{1, 2, 3, 2, 2};
    Solution sol;
    output(sol.intersect(v1, v2));
    return 0;
}

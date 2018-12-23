/*
 * =====================================================================================
 *
 *       Filename:  search-a-2d-matrix-74.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月15日 09时45分12秒
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
    bool searchMatrix(vector<vector<int>>& matrix, int target)
    {
        int i = lower_bound(matrix, target);
        if (i == (int)matrix.size() || matrix[i][0] > target)
            --i;
        if (i == -1)
            return false;
        int j = lower_bound1(matrix[i], target);
        if (j == (int)matrix[i].size() || matrix[i][j] != target)
            return false;
        return true;
    }

    int lower_bound1(vector<int>& nums, int target)
    {
        int l = 0, r = nums.size() - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (target > nums[mid])
                l = mid + 1;
            else
                r = mid - 1;
        }
        return l;
    }

    int lower_bound(vector<vector<int>>& matrix, int target)
    {
        int l = 0, r = matrix.size() - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (target > matrix[mid][0])
                l = mid + 1;
            else
                r = mid - 1;
        }
        return l;
    }
};

int main(void)
{
    vector<vector<int>> m {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
    Solution sol;
    std::cout << sol.searchMatrix(m, 10) << std::endl;
    return 0;
}

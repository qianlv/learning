/*
 * =====================================================================================
 *
 *       Filename:  unique-paths-II-63.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月14日 20时42分27秒
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
    int uniquePathsWithObstacles(vector<vector<int>>& nums)
    {
        int m = nums.size();
        if (m == 0) return 1;
        int n = nums[0].size();
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                f[i][j] = 0;

        for (int i = 0; i < m; ++i)
        {
            if (nums[i][0] == 1) break;
            f[i][0] = 1;
        }
        for (int i = 0; i < n; ++i)
        {
            if (nums[0][i] == 1) break;
            f[0][i] = 1;
        }

        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
            {
                if (nums[i][j] == 1)
                    continue;
                f[i][j] = f[i - 1][j] + f[i][j-1];
            }
        return f[m - 1][n - 1];
    }

    int f[101][101];
};

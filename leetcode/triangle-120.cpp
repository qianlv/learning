/*
 * =====================================================================================
 *
 *       Filename:  triangle-120.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月17日 16时32分53秒
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
    int minimumTotal(vector<vector<int>>& triangle)
    {
        int m = triangle.size();
        if (m == 0) return 0;
        vector<vector<int>> f;
        for (auto v : triangle)
           f.push_back(vector<int>(v.size(), INT32_MAX));
        
        f[0][0] = triangle[0][0];
        for (int i = 1; i < m; ++i)
        {
            int n = triangle[i].size();
            for (int j = 0; j < n; ++j) 
            {
                if (j == 0) f[i][j] = f[i - 1][j] + triangle[i][j];
                else if (j == n - 1) f[i][j] = f[i - 1][j - 1] + triangle[i][j];
                else
                {
                    f[i][j] = std::min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j];
                }
                //std::cout << f[i][j] << std::endl;
            }
        }

        int res = INT32_MAX;
        for (int j = 0; j < (int)triangle[m - 1].size(); ++j)
            res = std::min(res, f[m - 1][j]);
        return res;
    }
};

int main(void)
{
    vector<vector<int>> nums{{-10}};
    Solution sol;
    std::cout << sol.minimumTotal(nums) << std::endl;
    return 0;
}

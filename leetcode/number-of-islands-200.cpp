/*
 * =====================================================================================
 *
 *       Filename:  number-of-islands-200.cpp
 *
 *    Description:  number of islands
 *
 *        Version:  1.0
 *        Created:  2016年06月11日 17时29分03秒
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
    int numIslands(vector<vector<char>>& grid)
    {
        int res = 0;
        for (int i = 0; i < (int)grid.size(); ++i)
        {
            for (int j = 0; j < (int)grid[i].size(); ++j)
            {
                if (grid[i][j] == '1')
                {
                    ++res;
                    floods(grid, i, j);
                }
            }
        }
        return res;
    }

    void floods(vector<vector<char>>& grid, int l, int r)
    {
        grid[l][r] = '0';
        if (l + 1 < (int)grid.size() && grid[l+1][r] == '1')
            floods(grid, l + 1, r);
        if (l - 1 >= 0 && grid[l - 1][r] == '1')
            floods(grid, l - 1, r);
        if (r + 1 < (int)grid[l].size() && grid[l][r+1] == '1')
            floods(grid, l, r + 1);
        if (r - 1 >= 0 && grid[l][r-1] == '1')
            floods(grid, l, r -1);
    }
};

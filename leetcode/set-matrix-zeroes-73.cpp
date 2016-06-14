/*
 * =====================================================================================
 *
 *       Filename:  set-matrix-zeroes-73.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月14日 21时30分34秒
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
    void setZeroes(vector<vector<int>>& matrix)
    {
        int m = matrix.size();
        if (m == 0) return;
        int n = matrix[0].size();
        
        bool flag_row = false, flag_col = false;
        for (int i = 0; i < m; ++i) 
        {
            for (int j = 0; j < n; ++j) 
            {
                if (matrix[i][j] == 0)
                {
                    if (i == 0) flag_row = true;
                    if (j == 0) flag_col = true;
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
               if (matrix[i][0] == 0 || matrix[0][j] == 0)
                   matrix[i][j] = 0;
            }
        }
        if (flag_row)
        {
            for (int i = 0; i < n; ++i) {
               matrix[0][i] = 0; 
            }
        }
        if (flag_col)
        {
            for (int i = 0; i < m; ++i) {
               matrix[i][0] = 0;
            }
        }
    }
};

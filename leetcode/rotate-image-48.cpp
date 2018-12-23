/*
 * =====================================================================================
 *
 *       Filename:  rotate-image-48.cpp
 *
 *    Description:  90度
 *
 *        Version:  1.0
 *        Created:  2016年06月14日 14时17分57秒
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
    void rotate(vector<vector<int>>& matrix)
    {
        int n = matrix.size();
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = i; j < n - i - 1; ++j)
            {
                int tmp = matrix[i][j];
                //matrix[i][j] = matrix[j][n - 1 - i];
                //matrix[j][n - 1 -i] =  matrix[n - 1 - i][n - 1 - j];
                //matrix[n - 1 - i][n - 1 - j] = matrix[n - 1 - j][i];
                //matrix[n - 1 - j][i] = tmp;

                matrix[i][j] = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 -i][n - 1 - j];
                matrix[n - 1 -i][n - 1 - j] = matrix[j][n - 1 - i];
                matrix[j][n - 1 - i] = tmp;
            }
            //std::cout << "---" << std::endl;
        }
    }
};  

int main(void)
{
    vector<vector<int>> v{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Solution sol;
    sol.rotate(v);
    return 0;
}

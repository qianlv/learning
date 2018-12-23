/*
 * =====================================================================================
 *
 *       Filename:  spiral-matrix-54.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月14日 17时00分46秒
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
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        int m = matrix.size();
        if (m == 0) return {};
        int n = matrix[0].size();
        vector<int> res;
        for (int i = 0; i < (std::min(n, m) + 1) / 2; ++i)
        {
            //std::cout << "i=" << i << std::endl;
            for (int j = i; j < n - i; j++)
            {
                //std::cout << "wa" << std::endl;
                res.push_back(matrix[i][j]);
            }

            for (int j = i + 1; j < m - i; ++j)
            {
                //std::cout << "---" << std::endl;
                res.push_back(matrix[j][n - i - 1]);
            }

            if (m - i - 1 != i)
            {
                //std::cout << "-" << std::endl;
                //std::cout << n - i - 2 << std::endl;
                for (int j = n - i - 2; j >= i; --j)
                {
                    res.push_back(matrix[m - i - 1][j]);
                }
            }

            if (n - i - 1 != i)
            {
                //std::cout << m - i - 2 << std::endl;
                for (int  j = m - i - 2; j >= i + 1; --j)
                {
                    res.push_back(matrix[j][i]);
                }
            }
        }
        return res;
    }
};

int main(void)
{
    vector<vector<int>> m {{1, -1}, {2, -2}, {3, -3}};
    //vector<vector<int>> m {{1, 2, 3}, {1, 2, 3}};
    //vector<vector<int>> m {{3}, {2}, {1}, {-1}};
    Solution sol;
    output(sol.spiralOrder(m));
    return 0;
}

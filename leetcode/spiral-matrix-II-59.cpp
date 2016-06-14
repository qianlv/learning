/*
 * =====================================================================================
 *
 *       Filename:  spiral-matrix-II-59.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月14日 19时54分03秒
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
    vector<vector<int>> generateMatrix(int n)
    {
        if (n == 0) return {};
        vector<vector<int>> res;
        res.resize(n);
        for (int i = 0; i < n; ++i)
            res[i].resize(n);
        int cnt = 1;
        for (int i = 0; i < (n + 1) / 2; ++i)
        {
            for (int j = i; j < n - i; j++)
            {
                res[i][j] = cnt++;
            }

            for (int j = i + 1; j < n - i; ++j)
            {
                res[j][n - i - 1] = cnt++;
            }

            if (n - i - 1 != i)
            {
                for (int j = n - i - 2; j >= i; --j)
                {
                    res[n - i - 1][j] = cnt++;
                }
            }

            if (n - i - 1 != i)
            {
                for (int  j = n - i - 2; j >= i + 1; --j)
                {
                    res[j][i] = cnt++;
                }
            }
        }
        return res;
    }
};

int main(void)
{
    Solution sol;
    auto res = sol.generateMatrix(4);
    for (auto iter : res)
        output(iter);
    return 0;
}

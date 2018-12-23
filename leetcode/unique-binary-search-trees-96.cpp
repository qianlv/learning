/*
 * =====================================================================================
 *
 *       Filename:  unique-binary-search-trees-96.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月15日 19时16分39秒
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
    int numTrees(int n)
    {
        dp.clear();
        dp.resize(n + 1, 0);
        dp[0] = 1;
        dfs(n);
        return dp[n];
    }

    void dfs(int n)
    {
        if (dp[n] != 0) return;
        for (int i = 0; i < n; ++i) {
            dfs(i); dfs(n - i - 1);
            dp[n] += dp[i] * dp[n - i - 1];
        }
    }
    vector<int> dp;
};

int main(void)
{
    Solution sol;
    std::cout << sol.numTrees(6) << std::endl;
    return 0;
}

/*
 * =====================================================================================
 *
 *       Filename:  edit-distance-72.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月15日 14时06分02秒
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
    int minDistance(string word1, string word2)
    {
        int len1 = word1.size() + 1, len2 = word2.size() + 1;
        vector<vector<int>> f(2, vector<int>(len1, 0));

        for (int i = 0; i < len1; ++i)
        {
            //std::cout << i << " ";
            f[0][i] = i;
        }
        std::cout << endl;

        int tmp = 1; 
        for (int i = 1; i < len2; ++i)
        {
            for (int j = 0; j < len1; ++j)
            {
                if (j == 0) f[tmp][j] = f[1-tmp][j] + 1;    /* 空白 */
                else
                {
                    if (word2[i - 1] == word1[j - 1])
                    {
                        f[tmp][j] = f[1 - tmp][j - 1];
                    }
                    else
                        f[tmp][j] = std::min(std::min(f[1 - tmp][j], f[1 - tmp][j - 1]), f[tmp][j - 1]) + 1;
                }
                //std::cout << f[tmp][j] << " ;
            }
            //std::cout << std::endl;
            tmp = 1 - tmp;
        }
        return f[1 - tmp][len1 - 1];

    }
};

int main(void)
{
    Solution sol;
    std::cout << sol.minDistance("horse", "ros") << std::endl;
    return 0;
}

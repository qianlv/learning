/*
 * =====================================================================================
 *
 *       Filename:  wildcard-matching-44.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月15日 11时05分55秒
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
#include <string>
using namespace std;

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int count = 0;
        int plen = p.size();
        int slen = s.size();
        for (int i = 0; i < plen; ++i)
            if (p[i] == '*') count++;
        if ((count == 0 && plen != slen) || (plen - count > slen)) return false;
        vector<vector<bool>> f(s.size() + 1, vector<bool>(p.size() + 1, false));
        f[0][0] = true;
        for (int i = 0; i < (int)p.size(); ++i)      /* 空字符串匹配 */
        {
            if (p[i] == '*') f[0][i + 1] = f[0][i];
        }
        for (size_t i = 0; i < s.size(); ++i)
        {
            for (size_t j = 0; j < p.size(); ++j) {
                if (s[i] == p[j] || p[j] == '?')
                    f[i + 1][j + 1] = f[i][j];
                else if (p[j] == '*') 
                {
                    if (j != 0 && p[j] == p[j -1])
                    {
                        f[i+1][j+1] = f[i + 1][j];
                        continue;
                    }
                    f[i + 1][j + 1] = f[i + 1][j] || f[i][j + 1];
                }
            }
        }
        return f[s.size()][p.size()];
    }
};

int main(void)
{
    Solution sol;
    std::cout << sol.isMatch("aa", "a") << std::endl;
    std::cout << sol.isMatch("aa", "aa") << std::endl;
    std::cout << sol.isMatch("aaa", "aa") << std::endl;
    std::cout << sol.isMatch("aa", "*") << std::endl;
    std::cout << sol.isMatch("aa", "a*") << std::endl;
    std::cout << sol.isMatch("ab", "?*") << std::endl;
    std::cout << sol.isMatch("aab", "c*a*b") << std::endl;
    //0 1 0 0 1 1
    return 0;
}

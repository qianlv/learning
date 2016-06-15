/*
 * =====================================================================================
 *
 *       Filename:  interleaving-string-97.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月15日 20时23分40秒
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
    bool isInterleave(string s1, string s2, string s3)
    {
        int len1 = s1.length();
        int len2 = s2.length();
        int len3 = s3.length();
        if (len1 + len2 != len3) return false;
        if (len1 == 0 && s2 != s3) return false;
        if (len2 == 0 && s1 != s3) return false;
        vector<vector<bool>> f(len1 + 1, vector<bool>(len2 + 1, false));
        f[0][0] = true;
        for (int i = 0; i < len2; ++i)
            if (s2[i] == s3[i]) f[0][i + 1] = f[0][i];
        //output(f[0]);

        for (int i = 1; i < len1 + 1; ++i)
        {
            for (int j = 0; j < len2 + 1; ++j)
            {
                if (j == 0)
                {
                    f[i][j] = f[i - 1][j] && s1[i - 1] == s3[i -1];
                }
                else
                {
                    //std::cout << "i + j - 1 = " << i + j - 1 << std::endl;
                    f[i][j] = f[i][j] || (f[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
                    f[i][j] = f[i][j] || (f[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
                }
            }
            //output(f[i]);
        }
        return f[len1][len2];
    }
};

int main(void)
{
    Solution sol;
    std::cout << sol.isInterleave("ab", "abc", "ababc") << std::endl;
    std::cout << sol.isInterleave("aabcc", "dbbca", "aadbbcbcac") << std::endl;
    std::cout << sol.isInterleave("aabcc", "dbbca", "aadbbbaccc") << std::endl;
    return 0;
}

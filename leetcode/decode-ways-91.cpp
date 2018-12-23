/*
 * =====================================================================================
 *
 *       Filename:  decode-ways-91.cpp
 *
 *    Description:  decode
 *
 *        Version:  1.0
 *        Created:  2016年06月15日 17时02分46秒
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
    int numDecodings(string s)
    {
        if (s.size() == 0) return 0;
        vector<int> f(s.size(), 0);
        if (s[0] != '0') f[0] = 1;

        for (int i = 1; i < (int)s.size(); ++i)
        {
            int val = s[i] - '1' + 1;
            if (val != 0)
                f[i] = f[i - 1];

            if (s[i - 1] != '0')
            {
                val = (s[i - 1] - '1' + 1) * 10 + (s[i] - '1' + 1);
                if (val >= 1 && val <= 26)
                    f[i] += i - 2 >= 0 ? f[i - 2] : 1;
            }
        }
        return f[s.size() - 1];
    }
};

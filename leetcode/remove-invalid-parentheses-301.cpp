/*
 * =====================================================================================
 *
 *       Filename:  remove-invalid-parentheses-301.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月11日 19时36分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    vector<string> removeInvalidParentheses(string s)
    {
        int left = 0, right = 0;
        for (auto c : s)
        {
            if (c == '(') ++left;
            else if (c == ')') left > 0 ? --left : ++right;
        }
        string res_s;
        unordered_set<string> res;
        dfs(s, 0, res_s, res, left, right, 0);
        return vector<string>(res.begin(), res.end());
    }

    void dfs(string& s, int pos, string res_s, unordered_set<string>& res, int left, int right, int pair)
    {
        if (s[pos] == '\0')
        {
            if (!pair)
                res.insert(res_s);
            return;
        }

        if (s[pos] == '(')
        {
            if (left) dfs(s, pos + 1, res_s, res, left - 1, right, pair);
            dfs(s, pos + 1, res_s + s[pos], res, left, right, pair + 1);
        }
        else if (s[pos] == ')') 
        {
            if (right) dfs(s, pos + 1, res_s, res, left, right - 1, pair);
            if (pair) dfs(s, pos + 1, res_s + s[pos], res, left, right, pair - 1);
        }
        else
        {
            dfs(s, pos + 1, res_s + s[pos], res, left, right, pair);
        }
    }
};

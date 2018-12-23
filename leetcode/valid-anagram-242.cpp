/*
 * =====================================================================================
 *
 *       Filename:  valid-anagram-242.cpp
 *
 *    Description:  valid anagram
 *
 *        Version:  1.0
 *        Created:  2016年06月02日 16时00分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        if (s.size() != t.size())
            return false;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

/*
 * =====================================================================================
 *
 *       Filename:  H-index-275.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月03日 11时09分46秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int hIndex(vector<int>& citations)
    {
        // std::sort(citations.begin(), citations.end());
        for (int i = citations.size() - 1; i >= 0; --i)
        {
            if (int(citations.size() - i - 1) >= citations[i])
            {
                return int(citations.size() - i - 1);
            }
        }
        return citations.size();
    }
};

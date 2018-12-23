/*
 * =====================================================================================
 *
 *       Filename:  H-index-274.cpp
 *
 *    Description:  H index
 *
 *        Version:  1.0
 *        Created:  2016年06月03日 10时57分40秒
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
        std::sort(citations.begin(), citations.end(), std::greater<int>());
        for (size_t i = 0; i < citations.size(); ++i)
        {
            if ((int)i >= citations[i])
            {
                return i;
            }
        }
        return citations.size();
    }
};

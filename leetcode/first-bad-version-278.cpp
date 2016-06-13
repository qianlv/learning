/*
 * =====================================================================================
 *
 *       Filename:  first-bad-version-278.cpp
 *
 *    Description:  二分
 *
 *        Version:  1.0
 *        Created:  2016年06月13日 10时57分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Forward declaration
bool isBadVersion(int version);

class Solution
{
public:
    int firstBadVersion(int n)
    {
        int l = 0, r = n - 1;
        while (l <= r)
        {
            int mid = l + (r - l) / 2;
            if (!isBadVersion(mid + 1))
            {
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        return l + 1;
    }


};


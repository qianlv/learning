/*
 * =====================================================================================
 *
 *       Filename:  divide-two-integers-29.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月16日 17时42分12秒
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
#include <climits>
using namespace std;

class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        if (divisor == 0 || (dividend == INT32_MIN && divisor == -1))
            return INT32_MAX;
        bool flag = false;
        if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0))
            flag = true;
        
        long divd = std::abs((long)dividend);
        long divr = std::abs((long)divisor);
        long res = 0;
        long count = 1;
        long tmp = divr;
        while (tmp <= divd)
        {
            tmp += tmp;
            count += count;
        }

        while (true)
        {
            while (divd >= tmp)
            {
                res += count;
                divd -= tmp;
            }

            if (divd < tmp)
            {
                tmp >>= 1;
                count >>= 1;
            }
            if (divd == 0 || tmp == 0)
                break;
        }

        std::cout << res << std::endl;

        if (flag) return -res;
        return res;
    }
};

int main(void)
{
    Solution sol;
    std::cout << sol.divide(2147483647, 1) << std::endl;
    return 0;
}

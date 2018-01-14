/*
 * =====================================================================================
 *
 *       Filename:  remove-k-digits-402.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年12月01日 14时29分47秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;


class Solution {
public:
    string removeKdigits(string num, int k) {
        bool dels[10002] = {false};
        int len = num.size();
        for(int i = 0; i < k; i++) {
            int pre = 0;
            while (dels[pre] && pre < len) {
                pre++;
            }
            bool flag = false;
            for (int j = pre + 1; j < len; ++j) {
                if(dels[j]) continue;
                if(num[pre] > num[j]) {
                    dels[pre] = true;
                    flag = true;
                    break;
                }
                pre = j;
            }
            if (!flag) {
                dels[pre] = true;
            }
        }
        string res;
        bool first = true;
        for(int i = 0; i < len; ++i) {
            if (!dels[i]) {
                if (num[i] != '0') {
                    first = false;
                } else if (first) {
                    continue;
                }
                res.push_back(num[i]);
            }
        }
        if (res.size() == 0) {
            return "0";
        }
        return res;
    }
};


int main()
{
    Solution solve = Solution();
    std::cout << solve.removeKdigits("1432219", 3) << std::endl;
    std::cout << solve.removeKdigits("10200", 1) << std::endl;
    std::cout << solve.removeKdigits("10", 2) << std::endl;
    std::cout << solve.removeKdigits("106573", 3) << std::endl;
    return 0;
}

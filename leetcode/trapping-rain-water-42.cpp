/*
 * =====================================================================================
 *
 *       Filename:  trapping-rain-water-42.cpp
 *
 *    Description:  单调栈
 *
 *        Version:  1.0
 *        Created:  2016年06月13日 15时59分44秒
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
#include <stack>
using namespace std;

class Solution
{
public:
    int trap(vector<int>& height)
    {
        int res = 0;
        for (int i = 0; i < (int)height.size(); ++i)
        {
            if (stack_.empty())
            {
                stack_.push(i);
                continue;
            }

            int tmp = 0;
            int pre_len = 0;
            int j = -1;
            int pre_j = -1;
            while (!stack_.empty())
            {
                j = stack_.top();
                //std::cout << height[j] << "-" << height[i] << std::endl;
                if (height[j] < height[i])
                {
                    tmp += height[j] * (i - j - pre_len);
                    pre_len = i - j;
                    pre_j = j;
                    stack_.pop();
                }
                else
                {
                    break;
                }
            }
            res += std::min(height[j], height[i]) * pre_len - tmp;
            //std::cout << "len=" << pre_len << "res=" << res << "tmp=" << tmp<< std::endl;
            if (height[j] != height[i])
            {
                if (height[j] > height[i] && pre_j != -1)
                {
                    height[pre_j] = height[i];
                    stack_.push(pre_j);
                }
                else
                {
                    stack_.push(i);
                }
            }
        }
        return res;
    }

    std::stack<int> stack_;
};

int main(void)
{
    std::vector<int> height {
        0,1,0,2,1,0,1,3,2,1,2,1
    };
    Solution sol;
    std::cout << sol.trap(height) << std::endl;
    return 0;
}

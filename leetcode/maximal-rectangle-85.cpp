/*
 * =====================================================================================
 *
 *       Filename:  maximal-rectangle-85.cpp
 *
 *    Description:  单调栈(递增)
 *
 *        Version:  1.0
 *        Created:  2016年06月15日 15时56分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <stack>
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
    int maximalRectangle(vector<vector<char>>& matrix)
    {
        int m = matrix.size();
        if (m == 0) return 0;
        int n = matrix[0].size();
        vector<vector<int>> ma(m, vector<int>(n, 0));
        int max_area = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j) 
            {
                if (i == 0) ma[i][j] = (matrix[i][j] == '1' ? 1 : 0); 
                else
                {
                    if (matrix[i][j] == '1') ma[i][j] = ma[i - 1][j] + 1;
                }
            }
            output(ma[i]);
            max_area = std::max(largestRectangel(ma[i]), max_area);
        }
        return max_area;
    }

    int largestRectangel(vector<int>& nums)
    {
        int max_area = 0;
        stack<pair<int, int>> stack_;
        for (int i = 0; i < (int)nums.size(); ++i)
        {
            max_area = std::max(max_area, nums[i]);
            if (stack_.empty())
            {
                stack_.push(make_pair(i, nums[i]));
                continue;
            }
            
            std::pair<int, int> top{-1, -1};
            std::pair<int, int> pre_top{-1, -1};
            while (!stack_.empty())
            {
                top = stack_.top();
                if (nums[i] <= top.second)
                {
                    stack_.pop();
                    pre_top = top;
                    max_area = std::max(max_area, (i - top.first) * top.second);
                }
                else
                {
                    break;
                }
            }
            //std::cout << top.first << std::endl;
            if (pre_top.first != -1)
            {
                max_area = std::max(max_area, (i - pre_top.first + 1) * nums[i]);
                stack_.push(make_pair(pre_top.first, nums[i]));
            }
            else
            {
                stack_.push(make_pair(i, nums[i]));
            }
        }
        return max_area;
    }
};

int main(void)
{
    vector<vector<char>> m{{'0','1', '1', '0'}, {'0','1', '1', '1'}, {'0', '0', '0', '1'}};
    Solution sol;
    std::cout << sol.maximalRectangle(m) << std::endl;
    return 0;
}

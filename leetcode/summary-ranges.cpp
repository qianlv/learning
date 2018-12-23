/*
 * =====================================================================================
 *
 *       Filename:  summary-ranges.cpp
 *
 *    Description:  summary-ranges
 *
 *        Version:  1.0
 *        Created:  2016年04月28日 21时52分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

class Solution
{
public:
    vector<string> summaryRanges(vector<int>& nums)
    {
        int b = -1;
        vector<string> ret;
        if (nums.size() == 0)
        {
            return ret;
        }
        nums.push_back(nums[nums.size()-1] + 2);
        for (size_t i = 1, j = 0; i < nums.size(); ++i, ++j)
        {
            if (nums[i] != nums[j] + 1)
            {
                string value;
                if (j - b == 1)
                {
                    value = to_string(nums[j]);
                }
                else
                {
                    value = to_string(nums[b + 1]) + "->" + to_string(nums[j]);
                }
                ret.push_back(value);
                b = j;
            }
        }
        return ret;
    }
};

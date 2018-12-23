/*
 * =====================================================================================
 *
 *       Filename:  merge-intervals-56.cpp
 *
 *    Description:  merge intervals 
 *
 *        Version:  1.0
 *        Created:  2016年06月02日 09时52分33秒
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

struct Interval
{
    int start;
    int end;
    Interval() : start(0), end(0) { }
    Interval(int s, int e) : start(s), end(e) { }
};

void output(const std::vector<Interval>& intervals)
{
    std::for_each(intervals.begin(), intervals.end(),
                [](const Interval& v) {
                    cout << v.start << "->" << v.end << " ";
                });
    cout << endl;
}

class Solution
{
public:
    vector<Interval> merge(vector<Interval>& intervals)
    {
        if (intervals.size() <= 1)
            return intervals;
        sort(intervals.begin(), intervals.end(), 
            [](const Interval& l, const Interval& r) {
                return l.start < r.start || (l.start == r.start && l.end < r.end);
            });
        // output(intervals);

        std::vector<Interval> res;
        Interval pre = intervals[0];
        for (auto iter = intervals.begin() + 1;
                iter != intervals.end(); ++iter)
        {
            if (pre.end >= iter->start)
            {
                pre.end = std::max(pre.end, iter->end);
            }
            else
            {
                res.push_back(pre);
                pre = *iter;
            }
        }

        res.push_back(pre);
        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<Interval> v = { {2, 6}, {1, 3}, {8, 10}, {15, 18}};
    std::vector<Interval> res = sol.merge(v);
    output(res);
}

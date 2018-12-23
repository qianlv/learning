/*
 * =====================================================================================
 *
 *       Filename:  insert-interval-57.cpp
 *
 *    Description:  insert interval
 *
 *        Version:  1.0
 *        Created:  2016年06月02日 10时15分52秒
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
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
    {
        std::vector<Interval> res;
        res.reserve(intervals.size() + 1);

        for (auto iter = intervals.begin();
                iter != intervals.end(); ++iter)
        {
            if (iter->end < newInterval.start)
            {
                res.push_back(*iter);
            }
            else if (iter->end >= newInterval.start) 
            { 
                if (iter->start > newInterval.end)
                {
                    res.push_back(newInterval);
                    newInterval = {3, 2};
                    res.insert(res.end(), iter, intervals.end());
                    break;
                }

                if (iter->start <= newInterval.start && iter->end >= newInterval.end)
                {
                    res.insert(res.end(), iter, intervals.end());
                    newInterval = {3, 2};
                    break;
                }

                if (iter->start < newInterval.start && iter->end >= newInterval.start)
                {
                    newInterval.start = iter->start;
                }
                else if (iter->start <= newInterval.end && iter->end > newInterval.end) 
                {
                    newInterval.end = iter->end;
                }
            }
        }

        if (newInterval.start <= newInterval.end)
            res.push_back(newInterval);
        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<Interval> v = { {1, 5}};
    std::vector<Interval> res = sol.insert(v, Interval(1, 3));
    std::vector<Interval> v2 = {{}};
    output(res);
}

/*
 * =====================================================================================
 *
 *       Filename:  course-schedule-II-210.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月11日 18时53分23秒
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
#include <queue>
using namespace std;

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prereqisites)
    {
        indegree.resize(numCourses);
        adjacency_list.resize(numCourses);
        for (auto elem : prereqisites)
        {
            ++indegree[elem.first];
            adjacency_list[elem.second].push_back(elem.first);
        }
        for (int i = 0; i < numCourses; ++i)
            if (indegree[i] == 0) zeroPoint.push(i);
        bfs();
        if ((int)res.size() != numCourses)
            return vector<int>();
        return res;
    }

    void bfs()
    {
        while (!zeroPoint.empty())
        {
            int u = zeroPoint.front();
            res.push_back(u);
            zeroPoint.pop();
            for (auto v : adjacency_list[u])
            {
                --indegree[v];
                if (indegree[v] == 0)
                    zeroPoint.push(v);
            }
        }
    }
    
    queue<int> zeroPoint;
    vector<int> indegree;
    vector<vector<int>> adjacency_list;
    vector<int> res;
};

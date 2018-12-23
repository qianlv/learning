/*
 * =====================================================================================
 *
 *       Filename:  reconstruct-ltinerary-332.cpp
 *
 *    Description:  欧拉图
 *
 *        Version:  1.0
 *        Created:  2016年06月12日 11时32分47秒
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
#include <unordered_set>
#include <set>
#include <map>
#include <string>
#include <unordered_map>
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
    vector<string> findItinerary(vector<pair<string, string>> tickets)
    {
        adjacency_list.clear();
        tickets_size = tickets.size();
        for (auto elem : tickets)
        {
            adjacency_list[elem.first].push_back(std::make_pair(elem.second, false));
        }
        for (auto& list : adjacency_list)
        {
            sort(list.second.begin(), list.second.end());
            //output(list.second);
        }
        vector<string> res;
        res.push_back("JFK");
        dfs(res, "JFK", 0);
        return res;
    }

    bool dfs(vector<string>& res, const string& pos, size_t len)
    {
        if (len == tickets_size)
        {
            return true;
        }

        for (auto& elem : adjacency_list[pos])
        {
            if (!elem.second)
            {
                elem.second = true;
                res.push_back(elem.first);
                if (dfs(res, elem.first, len + 1))
                {
                    return true;
                }
                res.pop_back();
                elem.second = false;
            }
        }
        return false;
    }
    
    size_t tickets_size;
    unordered_map<string, vector<pair<string, bool>>> adjacency_list;
};

int main(void)
{
    //vector<pair<string, string>> tickets {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
    //vector<pair<string, string>> tickets {{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}};
    //vector<pair<string, string>> tickets {{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}};
    //vector<pair<string, string>> tickets {{"AXA","EZE"},{"EZE","AUA"},{"ADL","JFK"},{"ADL","TIA"},{"AUA","AXA"},{"EZE","TIA"},{"EZE","TIA"},{"AXA","EZE"},{"EZE","ADL"},{"ANU","EZE"},{"TIA","EZE"},{"JFK","ADL"},{"AUA","JFK"},{"JFK","EZE"},{"EZE","ANU"},{"ADL","AUA"},{"ANU","AXA"},{"AXA","ADL"},{"AUA","JFK"},{"EZE","ADL"},{"ANU","TIA"},{"AUA","JFK"},{"TIA","JFK"},{"EZE","AUA"},{"AXA","EZE"},{"AUA","ANU"},{"ADL","AXA"},{"EZE","ADL"},{"AUA","ANU"},{"AXA","EZE"},{"TIA","AUA"},{"AXA","EZE"},{"AUA","SYD"},{"ADL","JFK"},{"EZE","AUA"},{"ADL","ANU"},{"AUA","TIA"},{"ADL","EZE"},{"TIA","JFK"},{"AXA","ANU"},{"JFK","AXA"},{"JFK","ADL"},{"ADL","EZE"},{"AXA","TIA"},{"JFK","AUA"},{"ADL","EZE"},{"JFK","ADL"},{"ADL","AXA"},{"TIA","AUA"},{"AXA","JFK"},{"ADL","AUA"},{"TIA","JFK"},{"JFK","ADL"},{"JFK","ADL"},{"ANU","AXA"},{"TIA","AXA"},{"EZE","JFK"},{"EZE","AXA"},{"ADL","TIA"},{"JFK","AUA"},{"TIA","EZE"},{"EZE","ADL"},{"JFK","ANU"},{"TIA","AUA"},{"EZE","ADL"},{"ADL","JFK"},{"ANU","AXA"},{"AUA","AXA"},{"ANU","EZE"},{"ADL","AXA"},{"ANU","AXA"},{"TIA","ADL"},{"JFK","ADL"},{"JFK","TIA"},{"AUA","ADL"},{"AUA","TIA"},{"TIA","JFK"},{"EZE","JFK"},{"AUA","ADL"},{"ADL","AUA"},{"EZE","ANU"},{"ADL","ANU"},{"AUA","AXA"},{"AXA","TIA"},{"AXA","TIA"},{"ADL","AXA"},{"EZE","AXA"},{"AXA","JFK"},{"JFK","AUA"},{"ANU","ADL"},{"AXA","TIA"},{"ANU","AUA"},{"JFK","EZE"},{"AXA","ADL"},{"TIA","EZE"},{"JFK","AXA"},{"AXA","ADL"},{"EZE","AUA"},{"AXA","ANU"},{"ADL","EZE"},{"AUA","EZE"}};

    Solution sol;
    output(sol.findItinerary(tickets));
    return 0;
}

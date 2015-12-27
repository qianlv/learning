/*
 * =====================================================================================
 *
 *       Filename:  9_31.cpp
 *
 *    Description:  9.31
 *
 *        Version:  1.0
 *        Created:  2015年12月26日 14时44分10秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <deque>
using std::deque;

#include <forward_list>
using std::forward_list;

int main()
{
    list<int> ilist = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto iter = ilist.begin();
    while (iter != ilist.end())
    {
        if (*iter % 2)
        {
            iter = ilist.insert(iter, *iter);
            ++iter;
            ++iter;
        }
        else
        {
            iter = ilist.erase(iter);
        }
    }
    for (auto &elem : ilist)
        cout << elem << " ";
    cout << endl;

    forward_list<int> fwlist = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto prev = fwlist.before_begin();
    auto cur = fwlist.begin();
    while (cur != fwlist.end())
    {
        if (*cur % 2)
        {
            cur = fwlist.insert_after(prev, *cur);
            ++cur;
            ++cur;
            ++prev;
            ++prev;
        }
        else
        {
            cur = fwlist.erase_after(prev);
        }
    }
    for (auto &elem : fwlist)
        cout << elem << " ";
    cout << endl;
}


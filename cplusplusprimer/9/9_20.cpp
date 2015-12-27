/*
 * =====================================================================================
 *
 *       Filename:  9_20.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月24日 21时13分43秒 CST
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

int main()
{
    list<int> ilist = {1, 4, 3, 10, 9, 4};
    deque<int> odd, even;
    for (auto iter = ilist.cbegin(); iter != ilist.cend(); ++iter)
    {
        if ((*iter) & 1)
        {
            odd.push_back(*iter);
        }
        else
        {
            even.push_back(*iter);
        }
    }

    for (auto iter = odd.cbegin(); iter != odd.cend(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    for (auto iter = even.cbegin(); iter != even.cend(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;
}

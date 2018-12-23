/*
 * =====================================================================================
 *
 *       Filename:  flatten-nested-list-iterator.cpp
 *
 *    Description:  flatten-nested-list-iterator
 *
 *        Version:  1.0
 *        Created:  2016年04月28日 20时50分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <deque>

class NestedIterator
{
public:
    NestedIterator(vector<NestedInteger> &nestedList)
    {
        init(nestedList);
    }

    void init(vector<NestedInteger> &nestedList)
    {
        for (vector<NestedInteger>::iterator iter = nestedList.begin();
             iter != nestedList.end(); ++iter)
        {
            if (iter->isInteger())
            {
                stack_.push_back(iter->getInteger());
            }
            else
            {
                init(iter->getList());
            }
        }

    }

    int next()
    {
        int res = stack_.front();
        stack_.pop_front();
        return res;
    }

    bool hasNext()
    {
        return !stack_.empty();
    }

private:
    std::deque<int> stack_;
};

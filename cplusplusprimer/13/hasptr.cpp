/*
 * =====================================================================================
 *
 *       Filename:  hasptr.cpp
 *
 *    Description:  Class HasPtr
 *
 *        Version:  1.0
 *        Created:  2016年01月10日 15时08分46秒 CST
 *       Revision:  none
 *       Compiler:  g++
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

#include <utility>

#include "hasptr.h"

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    cout << "swap(HasPtr &, HasPtr &)" << endl;
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

HasPtr::HasPtr(const string &s) :
    ps(new string(s)), i(0) 
{
    cout << "HasPtr(const string &s = string())" << endl;
}

HasPtr::HasPtr(const HasPtr &hp) :
    ps(new string(*hp.ps)), i(hp.i) 
{
    cout << "HasPtr(const HasPtr &hp) " << hp.ps << endl;
}

HasPtr::HasPtr(HasPtr &&p) noexcept :
    ps(p.ps), i(p.i) 
{
    p.ps = nullptr;
}

HasPtr::~HasPtr()
{
    cout << "~HasPtr()" << endl;
    delete ps;
}

// HasPtr& HasPtr::operator= (const HasPtr &rhs)
// {
//     cout << "operator= (const HasPtr &rhs)" << endl;
//     auto newp = new string(*rhs.ps);            /* 先拷贝数据, 避免rhs指向的是自己 */
//     delete ps;
//     ps = newp;
//     i = rhs.i;
//     return *this;
// }

HasPtr& HasPtr::operator= (HasPtr rhs)
{
    cout << "operator=" << endl;
    using std::swap;
    swap(*this, rhs);
    return *this;
}

bool HasPtr::operator< (const HasPtr &rhs) const
{
    return *ps < *rhs.ps;
}


void HasPtr::show()
{
    cout << *ps << endl;
}

HasPtrLikePointer::HasPtrLikePointer(const string &s) :
    ps(new string(s)), i(0), use(new size_t(1))
{
}

HasPtrLikePointer::HasPtrLikePointer(const HasPtrLikePointer &p) :
    ps(p.ps), i(p.i), use(p.use)
{
    ++*use;
}

HasPtrLikePointer::~HasPtrLikePointer()
{
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
}

HasPtrLikePointer& HasPtrLikePointer:: operator= (const HasPtrLikePointer &rhs)
{
    ++*rhs.use;
    if (--*use == 0)
    {
        delete ps;
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}

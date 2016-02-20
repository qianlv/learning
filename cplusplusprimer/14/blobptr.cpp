/*
 * =====================================================================================
 *
 *       Filename:  blobptr.cpp
 *
 *    Description:  Class Str Blob Ptr
 *
 *        Version:  1.0
 *        Created:  2016年01月06日 17时46分46秒 CST
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

#include <map>
using std::map;

#include <set>
using std::set;

#include <initializer_list>
using std::initializer_list;

#include <algorithm>
#include <numeric>
#include <memory>
#include <stdexcept>
using std::shared_ptr;
using std::weak_ptr;

#include "blob.h"
#include "blobptr.h"

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator++ ()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator-- ()
{
    --curr;
    check(curr, "increment past begin of StrBlobPtr");
    return *this;
}

StrBlobPtr StrBlobPtr::operator++ (int)
{
    StrBlobPtr ret = *this;
    ++*this;
    return ret;
}

StrBlobPtr StrBlobPtr::operator-- (int)
{
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}
StrBlobPtr& StrBlobPtr::operator+ (int n)
{
    check(curr + n, "increment past begin of StrBlobPtr");
    curr += n;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator- (int n)
{
    check(curr - n, "increment past end of StrBlobPtr");
    curr -= n;
    return *this;
}

string& StrBlobPtr::operator[] (size_t n)
{
    auto p = check(n, "dereference out of range");
    return (*p)[n];
}

const string& StrBlobPtr::operator[] (size_t n) const
{
    auto p = check(n, "dereference out of range");
    return (*p)[n];
}

string& StrBlobPtr::operator* () const
{
    auto p = check(curr, "dereference out of range");
    return (*p)[curr];
}

string* StrBlobPtr::operator-> () const
{
    return & this->operator*();
}

shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

const string& ConstStrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

string& ConstStrBlobPtr::operator[] (size_t n)
{
    auto p = check(n, "dereference out of range");
    return (*p)[n];
}

const string& ConstStrBlobPtr::operator[] (size_t n) const
{
    auto p = check(n, "dereference out of range");
    return (*p)[n];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

ConstStrBlobPtr& ConstStrBlobPtr::operator++ ()
{
    check(curr, "increment past end of ConstStrBlobPtr");
    ++curr;
    return *this;
}

ConstStrBlobPtr& ConstStrBlobPtr::operator-- ()
{
    --curr;
    check(curr, "increment past end of ConstStrBlobPtr");
    return *this;
}

ConstStrBlobPtr ConstStrBlobPtr::operator++ (int)
{
    ConstStrBlobPtr ret = *this;
    ++*this;
    return ret;
}

ConstStrBlobPtr ConstStrBlobPtr::operator-- (int)
{
    ConstStrBlobPtr ret = *this;
    --*this;
    return ret;
}

ConstStrBlobPtr& ConstStrBlobPtr::operator+ (int n)
{
    check(curr + n, "increment past begin of StrBlobPtr");
    curr += n;
    return *this;
}

ConstStrBlobPtr& ConstStrBlobPtr::operator- (int n)
{
    check(curr - n, "increment past end of StrBlobPtr");
    curr -= n;
    return *this;
}

const string& ConstStrBlobPtr::operator* () const
{
    auto p = check(curr, "dereference out of range");
    return (*p)[curr];
}

const string* ConstStrBlobPtr::operator-> () const
{
    return & this->operator*();
}

bool operator== (const StrBlobPtr &lbp, const StrBlobPtr &rbp)
{
    return lbp.curr == rbp.curr;
}
bool operator!= (const StrBlobPtr &lbp, const StrBlobPtr &rbp)
{
    return !(lbp == rbp);
}

bool operator< (const StrBlobPtr &lbp, const StrBlobPtr &rbp)
{
    return lbp.curr < lbp.curr;
}

bool operator<= (const StrBlobPtr &lbp, const StrBlobPtr &rbp)
{
    return !(rbp < lbp);
}

bool operator> (const StrBlobPtr &lbp, const StrBlobPtr &rbp)
{
    return rbp < lbp;
}

bool operator>= (const StrBlobPtr &lbp, const StrBlobPtr &rbp)
{
    return !(lbp < rbp);
}

bool operator== (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp)
{
    return lbp.curr == rbp.curr;
}

bool operator!= (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp)
{
    return !(lbp == rbp);
}

bool operator< (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp)
{
    return lbp.curr < lbp.curr;
}

bool operator<= (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp)
{
    return !(rbp < lbp);
}

bool operator> (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp)
{
    return rbp < lbp;
}

bool operator>= (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp)
{
    return !(lbp < rbp);
}


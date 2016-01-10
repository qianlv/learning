/*
 * =====================================================================================
 *
 *       Filename:  blobptr.h
 *
 *    Description:  Class Str Blob Ptr
 *
 *        Version:  1.0
 *        Created:  2016年01月06日 17时47分03秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BLOBPTR_H_
#define BLOBPTR_H_

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
using std::shared_ptr;
using std::weak_ptr;

#include "blob.h"

class StrBlobPtr
{
public:
    StrBlobPtr(): curr(0) { }
    StrBlobPtr(StrBlob &a, size_t sz = 0) :
        wptr(a.data), curr(sz) { }
    bool operator != (const StrBlobPtr &p)
    {
        return p.curr != curr;
    }
    string& deref() const;
    StrBlobPtr& incr();

private:
    shared_ptr<vector<string>> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

class ConstStrBlobPtr
{
public:
    ConstStrBlobPtr() : curr(0) { }
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : 
        wptr(a.data), curr(sz) { }
    bool operator != (const ConstStrBlobPtr &p)
    {
        return p.curr != curr;
    }
    const string& deref() const;
    ConstStrBlobPtr& incr();

private:
    shared_ptr<vector<string>> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

#endif // BLOBPTR_H_

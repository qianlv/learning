/*
 * =====================================================================================
 *
 *       Filename:  blob.cpp
 *
 *    Description:  StrBlob
 *
 *        Version:  1.0
 *        Created:  2016年01月05日 16时06分04秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "blob.h"
#include "blobptr.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
using std::make_shared;


StrBlob::StrBlob() : data(make_shared<vector<string>>()) 
{
}

StrBlob::StrBlob(initializer_list<string> il) :
    data(make_shared<vector<string>>(il))
{
}

void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

string& StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

const string& StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

const string& StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this); 
}

StrBlobPtr StrBlob::end()
{
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}

ConstStrBlobPtr StrBlob::cbegin() const
{
    return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::cend() const
{
    auto ret = ConstStrBlobPtr(*this, data->size());
    return ret;
}

bool operator== (const StrBlob &lsb, const StrBlob &rsb)
{
    return *lsb.data == *rsb.data;
}

bool operator!=  (const StrBlob &lsb, const StrBlob &rsb)
{
    return !(lsb == rsb);
}
string& StrBlob::operator[] (size_type n)
{
    check(n, "out of range");
    return data->at(n);
}
const string& StrBlob::operator[] (size_type n) const
{
    check(n, "out of range");
    return data->at(n);
}

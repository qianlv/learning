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
    friend bool operator== (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
    friend bool operator!= (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
    friend bool operator< (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
    friend bool operator<= (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
    friend bool operator> (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
    friend bool operator>= (const StrBlobPtr &lbp, const StrBlobPtr &rbp);

public:
    StrBlobPtr(): curr(0) { }
    StrBlobPtr(StrBlob &a, size_t sz = 0) :
        wptr(a.data), curr(sz) { }
    string& deref() const;
    StrBlobPtr& incr();
    string& operator[] (size_t n);
    const string& operator[] (size_t n) const;
    StrBlobPtr& operator++ ();
    StrBlobPtr& operator-- ();
    StrBlobPtr operator++ (int);
    StrBlobPtr operator-- (int);
    StrBlobPtr& operator+ (int);
    StrBlobPtr& operator- (int);
    string& operator* () const;
    string* operator-> () const;

private:
    shared_ptr<vector<string>> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

bool operator== (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
bool operator!= (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
bool operator< (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
bool operator<= (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
bool operator> (const StrBlobPtr &lbp, const StrBlobPtr &rbp);
bool operator>= (const StrBlobPtr &lbp, const StrBlobPtr &rbp);

class ConstStrBlobPtr
{
    friend bool operator== (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
    friend bool operator!= (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
    friend bool operator< (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
    friend bool operator<= (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
    friend bool operator> (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
    friend bool operator>= (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);

public:
    ConstStrBlobPtr() : curr(0) { }
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : 
        wptr(a.data), curr(sz) { }
    const string& deref() const;
    ConstStrBlobPtr& incr();
    string& operator[] (size_t n);
    const string& operator[] (size_t n) const;
    ConstStrBlobPtr& operator++ ();
    ConstStrBlobPtr& operator-- ();
    ConstStrBlobPtr operator++ (int);
    ConstStrBlobPtr operator-- (int);
    ConstStrBlobPtr& operator+ (int);
    ConstStrBlobPtr& operator- (int);
    const string& operator* () const;
    const string* operator-> () const;

private:
    shared_ptr<vector<string>> check(size_t, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

bool operator== (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
bool operator!= (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
bool operator< (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
bool operator<= (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
bool operator> (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);
bool operator>= (const ConstStrBlobPtr&lbp, const ConstStrBlobPtr &rbp);

#endif // BLOBPTR_H_

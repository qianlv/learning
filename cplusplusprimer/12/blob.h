/*
 * =====================================================================================
 *
 *       Filename:  blob.h
 *
 *    Description:  StrBlob
 *
 *        Version:  1.0
 *        Created:  2016年01月05日 16时06分40秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BLOB_H_
#define BLOB_H_

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
using std::make_shared;

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob
{
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
public:
    typedef vector<string>::size_type size_type;
    StrBlob();
    StrBlob(initializer_list<string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back(const string &t) { data->push_back(t); }
    void pop_back();
    string &front();
    const string &front() const;
    string &back();
    const string &back() const;

    StrBlobPtr begin();
    StrBlobPtr end();
    ConstStrBlobPtr cbegin() const;
    ConstStrBlobPtr cend() const;

private:    
    shared_ptr<vector<string>> data;
    void check(size_type i, const string &msg) const;
};

#endif

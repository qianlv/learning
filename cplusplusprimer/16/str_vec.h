/*
 * =====================================================================================
 *
 *       Filename:  str_vec.h
 *
 *    Description:  class StrVec
 *
 *        Version:  1.0
 *        Created:  2016年01月14日 15时03分45秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef STR_VEC_H_
#define STR_VEC_H_

#include <memory>
#include <string>
#include <utility>
#include <initializer_list>
using std::allocator;
using std::string;
using std::pair;
using std::initializer_list;

class StrVec
{
    friend bool operator== (const StrVec &lsv, const StrVec &rsv);
    friend bool operator!= (const StrVec &lsv, const StrVec &rsv);
    friend bool operator< (const StrVec &lsv, const StrVec &rsv);
    friend bool operator<= (const StrVec &lsv, const StrVec &rsv);
    friend bool operator> (const StrVec &lsv, const StrVec &rsv);
    friend bool operator>= (const StrVec &lsv, const StrVec &rsv);


public:
    StrVec():
        elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(initializer_list<string>);
    StrVec(const StrVec &);
    StrVec(StrVec &&) noexcept;
    StrVec& operator= (const StrVec &);
    StrVec& operator= (StrVec &&) noexcept;
    StrVec& operator= (initializer_list<string> il);
    ~StrVec();
    void push_back(const string &);
    void push_back(string &&);
    size_t size() const 
    {
        return first_free - elements;
    }
    size_t capacity() const
    {
        return cap - elements;
    }
    string* begin() const
    {
        return elements;
    }
    string* end() const
    {
        return first_free;
    }
    string& operator[] (size_t n)
    {
        return elements[n];
    }
    const string& operator[] (size_t n) const
    {
        return elements[n];
    }

    void reserve(size_t new_cap);
    void resize(size_t count);
    void resize(size_t count, const string &);
private:
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    pair<string *, string *> alloc_n_copy
        (const string *, const string *);
    void free();
    void reallocate();
    void alloc_n_move(size_t new_cap);
private:
    allocator<string> alloc; 
    string *elements;
    string *first_free;
    string *cap;
};

bool operator== (const StrVec &lsv, const StrVec &rsv);
bool operator!= (const StrVec &lsv, const StrVec &rsv);
bool operator< (const StrVec &lsv, const StrVec &rsv);
bool operator<= (const StrVec &lsv, const StrVec &rsv);
bool operator> (const StrVec &lsv, const StrVec &rsv);
bool operator>= (const StrVec &lsv, const StrVec &rsv);

#endif // STR_VEC_H_

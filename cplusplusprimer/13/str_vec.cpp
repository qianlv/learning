/*
 * =====================================================================================
 *
 *       Filename:  str_vec.cpp
 *
 *    Description:  class StrVec
 *
 *        Version:  1.0
 *        Created:  2016年01月14日 15时14分33秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cout;
using std::endl;

#include <memory>
#include <string>
#include <utility>
#include <initializer_list>
#include <algorithm>
using std::allocator;
using std::string;
using std::pair;
using std::uninitialized_copy;
using std::initializer_list;

#include "str_vec.h"

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec &&s) noexcept :
    elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec::StrVec(initializer_list<string> ils)
{
    auto newdata = alloc_n_copy(ils.begin(), ils.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
    free();
}

StrVec& StrVec::operator= (const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec& StrVec::operator= (StrVec &&rhs) noexcept
{
    if (this != &rhs)
    {
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

void StrVec::push_back(const string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

pair<string *, string *>
StrVec::alloc_n_copy(const string *b, const string *e)
{
    auto data = alloc.allocate(e - b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if (elements)
    {
        std::for_each(elements, first_free, [this] (string &rhs) { alloc.destroy(&rhs); });
//        for (auto p = first_free; p != elements; )
//            alloc.destory(--p);
//        alloc.deallocate(elements, cap - elements);
    }
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    alloc_n_move(newcapacity);
}

void StrVec::reserve(size_t new_cap)
{
    if (new_cap < capacity()) return;
    alloc_n_move(new_cap);
}

void StrVec::resize(size_t count)
{
    resize(count, string());
}

void StrVec::resize(size_t count, const string &s)
{
    if (count > size())
    {
        for (size_t i = size(); i != count; ++i)
            push_back(s);
    }
    else
    {
        while (first_free != elements + count)
            alloc.destroy(--first_free);
    }
}

void StrVec::alloc_n_move(size_t new_cap)
{
    if (new_cap > capacity())
    {
        auto first = alloc.allocate(new_cap);
        auto last = uninitialized_copy(make_move_iterator(begin()),
                                       make_move_iterator(end()),
                                       first);
        free();
        elements = fisrt;
        first_free = last;
        cap = first + new_cap;
    }
}

int main()
{
    StrVec svec = {"helo", "word", "one", "two"};
    svec.resize(1);
    for (auto s = svec.begin(); s != svec.end(); ++s)
        cout << *s << endl;
    svec.push_back("word");

    StrVec cvec = svec;
    StrVec ovec;
    ovec = svec;

    for (auto s = cvec.begin(); s != cvec.end(); ++s)
        cout << *s << endl;
    for (auto s = ovec.begin(); s != ovec.end(); ++s)
        cout << *s << endl;
}

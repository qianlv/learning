/*
 * =====================================================================================
 *
 *       Filename:  vec.h
 *
 *    Description:  template Vec 
 *
 *        Version:  1.0
 *        Created:  2016年02月24日 15时19分32秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef VEC_H_
#define VEC_H_

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <algorithm>
#include <initializer_list>
using std::cout;
using std::cin;
using std::endl;
using std::allocator;
using std::string;
using std::pair;
using std::initializer_list;
using std::uninitialized_copy;

template <typename T> class Vec;
template <typename T> bool operator== (const Vec<T> &lsv, const Vec<T> &rsv);
template <typename T> bool operator!= (const Vec<T> &lsv, const Vec<T> &rsv);
template <typename T> bool operator< (const Vec<T> &lsv, const Vec<T> &rsv);

template <typename T> class Vec
{
    friend bool operator== <T> (const Vec<T> &lsv, const Vec<T> &rsv);
    friend bool operator!= <T> (const Vec<T> &lsv, const Vec<T> &rsv);
    friend bool operator< <T> (const Vec<T> &lsv, const Vec<T> &rsv);

public:
    typedef size_t size_type;
    typedef T value_type;

public:
    Vec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(initializer_list<T> il)
    {
        auto newdata = alloc_n_copy(il.begin(), il.end());
        elements = newdata.first;
        first_free = cap = newdata.second;
    }
    Vec(const Vec &vec)
    {
        auto newdata = alloc_n_copy(vec.begin(), vec.end());
        elements = newdata.first;
        first_free = cap = newdata.second;
    }
    Vec(Vec &&vec) noexcept:
        elements(std::move(vec.elements)), first_free(std::move(vec.first_free)),
        cap(std::move(vec.cap))
    {
        vec.elements = vec.first_free = vec.cap = nullptr;
    }
    
    Vec& operator= (const Vec &r)
    {
        if (this != &r)
        {
            auto newdata = alloc_n_copy(r.begin(), r.end());
            free();
            elements = newdata.first;
            first_free = cap = newdata.second;
        }
        return *this;
    }
    Vec& operator= (Vec &&r) noexcept
    {
        if (this != &r)
        {
            free();
            elements = std::move(r.elements);
            first_free = std::move(r.first_free);
            cap = std::move(r.cap);
            r.elements = r.first_free = r.cap = nullptr;
        }
        return *this;
    }
    Vec& operator= (initializer_list<T> il)
    {
        auto newdata = alloc_n_copy(il.begin(), il.end());
        free();
        elements = newdata.first;
        first_free = cap = newdata.second;
    }

    ~Vec()
    {
        free();
    }

    void push_back(const T &v)
    {
        alloc_n_copy();
        alloc.construct(first_free++, v);
    }

    void push_back(T &&v)
    {
        alloc_n_copy();
        alloc.construct(first_free++, std::move(v));
    }

    size_t size() const
    {
        return first_free - elements;
    }

    size_t capacity() const
    {
        return cap - elements;
    }

    T* begin() const
    {
        return elements;
    }

    T* end() const
    {
        return first_free;
    }

    T& operator[] (size_t n)
    {
        return elements[n];
    }

    const T& operator[] (size_t n) const
    {
        return elements[n];
    }

    void reserve(size_t new_cap)
    {
        if (new_cap > capacity()) 
        {
            alloc_n_move(new_cap);
        }
    }

    void resize(size_t count)
    {
        resize(count, T());
    }

    void resize(size_t count, const T &v)
    {
        if (count > size())
        {
            for (size_t i = size(); i != count; ++i)
                push_back(v);
        }
        else
        {
            while (first_free != elements + count)
                alloc.destory(--first_free);
        }
    }
private:
    void chk_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    pair<T*, T*> alloc_n_copy(const T* b, const T* e)
    {
        auto p = alloc.allocate(e - b);
        return {p, uninitialized_copy(b, e, p)};
    }
    
    void free()
    {
        if (elements)
        {
            std::for_each(elements, first_free, [this] (T& v) { alloc.destroy(&v);});
            alloc.deallocate(elements, capacity());
        }
    }

    void alloc_n_move(size_t new_cap)
    {
        if (new_cap > capacity())
        {
            auto first = alloc.allocate(new_cap);
            auto last = uninitialized_copy(make_move_iterator(begin()),
                                           make_move_iterator(end()),
                                           first);
            free();
            elements = first;
            first_free = last;
            cap = first + new_cap;
        }
    }

    void reallocate()
    {
        auto newcapacity = size() ? 2 * size() : 1;    
        alloc_n_move(newcapacity);
    }
private:
    allocator<T> alloc;
    T *elements;
    T *first_free;
    T *cap;
};

template <typename T>
bool operator== (const Vec<T> &lsv, const Vec<T> &rsv)
{
    return lsv.size() == rsv.size() &&
        std::equal(lsv.begin(), lsv.end(), rsv.begin());
}

template <typename T>
bool operator!= (const Vec<T> &lsv, const Vec<T> &rsv)
{
    return !(lsv == rsv);
}

template <typename T>
bool operator< (const Vec<T> &lsv, const Vec<T> &rsv)
{
    return std::lexicographical_compare(lsv.begin(), lsv.end(),
            rsv.begin(), rsv.end());
}

#endif // VEC_H_

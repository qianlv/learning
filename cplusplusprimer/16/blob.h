/*
 * =====================================================================================
 *
 *       Filename:  blob.h
 *
 *    Description:  Class Blob.
 *
 *        Version:  1.0
 *        Created:  2016年02月23日 22时09分28秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BLOB_H_
#define BLOB_H_

#include <memory>
#include <algorithm>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

template <typename T> class BlobPtr;
template <typename T> class Blob;
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob
{
    friend class BlobPtr<T>;
    friend bool operator==<T> (const Blob<T> &lb, const Blob<T> &rb);

public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    Blob();
    Blob(std::initializer_list<T> il);
        template <typename It> Blob(It, It);
        size_type size() const
        {
            return data->size();
        }

        bool empty() const
        {
            return data->empty();
        }

        void push_back(const T &t)
        {
            data->push_back(t);
        }

        void push_back(T &&t)
        {
            data->push_back(std::move(t));
        }

        void pop_back();
        T& back();
        T& operator[] (size_type i);
        const T& operator[] (size_type i) const;

    private:
        std::shared_ptr<std::vector<T>> data;
        void check(size_type i, const std::string msg) const;
    };

    template <typename T>
    void Blob<T>::check(size_type i, const std::string msg) const
    {
        if (i >= size())
            throw std::out_of_range(msg);
    }

    template <typename T>
    T& Blob<T>::back()
    {
        check(0, "back on empty Blob");
        return data->back();
    }

    template <typename T>
    T& Blob<T>::operator[] (size_type i)
    {
        check(i, "subscript out of range");
        return (*data)[i];
    }

    template <typename T>
    const T& Blob<T>::operator[] (size_type i) const
    {
        check(i, "subscript out of range");
        return (*data)[i];
    }

    template <typename T>
    void Blob<T>::pop_back()
    {
        check(0, "pop_back on empty Blob");
        data->pop_back();
    }

    template <typename T>
    Blob<T>::Blob(): data(std::make_shared<std::vector<T>>())
    {
    }

    template <typename T>
    Blob<T>::Blob(std::initializer_list<T> il):
        data(std::make_shared<std::vector<T>>(il))
    {
#ifdef DEBUG
        cout << "Blob(std::initializer_list<T> il)" << endl;
#endif
    }

    template <typename T>
    template <typename It>
    Blob<T>::Blob(It b, It e):
        data(std::make_shared<std::vector<T>>(b, e))
{
#ifdef DEBUG
    cout << "Blob(It b, It e)" << endl;
#endif
}

template <typename T>
bool operator==(const Blob<T> &lb, const Blob<T> &rb)
{
    return *(lb.data) == *(rb.data);
}

template <typename T>
bool operator== (const BlobPtr<T> &, const BlobPtr<T> &);
template <typename T>
bool operator< (const BlobPtr<T> &, const BlobPtr<T> &);

template <typename T> class BlobPtr
{
    friend bool operator==<T> (const BlobPtr<T> &, const BlobPtr<T> &);
    friend bool operator< <T> (const BlobPtr<T> &, const BlobPtr<T> &);

public:
    BlobPtr(): curr(0) { }
    BlobPtr(Blob<T> &a, std::size_t sz = 0):
        wptr(a.data), curr(sz) { }
    T& operator*() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }

    BlobPtr& operator++();
    BlobPtr& operator--();
    BlobPtr operator++(int);
    BlobPtr operator--(int);

private:
    std::shared_ptr<std::vector<T>>
        check(std::size_t, const std::string &) const;
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;
};

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++()
{
    check(curr, "increment past end of BlobPtr");
    ++curr;
    return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
    --curr;
    check(curr, "increment past begin of BlobPtr");
    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
    BlobPtr ret = *this;
    --*this;
    return ret;
}

template <typename T>
bool operator== (const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    if (lhs.wptr.lock() != rhs.wptr.lock())
    {
        throw std::runtime_error("ptrs to different Blobs!");
    }
    return lhs.curr == rhs.curr;
}

template <typename T>
bool operator< (const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    if (lhs.wptr.lock() != rhs.wptr.lock())
    {
        throw std::runtime_error("ptrs to different Blobs!");
    }
    return lhs.curr < rhs.curr;
}

#endif // BLOB_H_

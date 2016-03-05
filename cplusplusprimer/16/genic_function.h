/*
 * =====================================================================================
 *
 *       Filename:  genic_function.h
 *
 *    Description:  Genic Function.
 *
 *        Version:  1.0
 *        Created:  2016年02月23日 20时54分23秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef GENIC_FUNCTION_H_
#define GENIC_FUNCTION_H_

#include <iterator>
#include <iostream>
#include <sstream>
#include <functional>
#include <utility>
#include <memory>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::less;

namespace ch16
{
    template<typename T, typename F = less<T>>
    int compare(const T &v1, const T &v2, F f = F())
    {
        if (f(v1, v2)) return -1;
        if (f(v2, v1)) return 1;
        return 0;
    }

    // template <>
    // int compare(const char* const &p1, const char* const &p2, int f)

    template<typename Iterator, typename T>
    Iterator find(Iterator first, Iterator last, const T& val)
    {
        while (first != last)
        {
            if (*first == val) return first;
            ++first;
        }
        return last;
    }

    template<typename T, size_t N>
    void print(T (&arr)[N])
    {
        for (const auto &elem : arr)
            cout << elem << endl;
    }

    template<typename T, size_t N>
    T* begin(T (&arr)[N])
    {
        return arr;
    }

    template<typename T, size_t N>
    T* end(T (&arr)[N])
    {
        return arr + N;
    }

    template<typename T, size_t N>
    constexpr size_t getsize(const T(&)[N])
    {
        return N;
    }

    // 16.19
    template <typename T>
    std::ostream& output(const T &container, std::ostream &os)
    {
        typedef typename T::size_type size_type;
        size_type sz = container.size();
        for (size_type i = 0; i < sz; ++i)
        {
            os << container[i] << " ";
        }
        return os;
    }
    
    // 16.20
    template <typename T>
    std::ostream& output2(const T &container, std::ostream &os)
    {
        for (auto iter = container.begin(); iter != container.end(); ++iter)
        {
            os << *iter << " ";
        }
        return os;
         
    }

    class DebugDelete
    {
    public:
        DebugDelete(std::ostream &s = std::cerr): os(s) { }
        template <typename T> void operator() (T *p) const
        {
            os << "delete unique_ptr" << std::endl;
            delete p;
        }
    private:
        std::ostream &os;
    };

    template <typename T>
    std::string debug_rep(const T &t)
    {
        std::ostringstream ret;
        ret << t;
        return ret.str();
    }

    template <typename T>
    std::string debug_rep(T *p)
    {
        std::ostringstream ret;
        ret << "pointer: " << p;
        if (p)
            ret << " " << debug_rep(*p);
        else
            ret << " null pointer";
        return ret.str();
    }

    template <> std::string debug_rep(const char *p);
    template <> std::string debug_rep(char *p);

    template <typename T>
    std::ostream &print1(std::ostream &os, const T &t)
    {
        return os << t;
    }
    
    template <typename T, typename... Args>
    std::ostream &print1(std::ostream &os, const T &t, const Args&... rest)
    {
        os << t << ", ";
#ifdef DEBUG
        cout << "(" << sizeof...(rest) << "), ";
#endif
        return print1(os, rest...);
    }

    template <typename... Args>
    std::ostream &errMsg(std::ostream &os, const Args&... rest)
    {
        return print1(os, debug_rep(rest)...);
    }

    template <typename T, typename... Args>
    auto make_shared(Args&&... rest) -> std::shared_ptr<T>
    {
        return std::shared_ptr<T>(new T(std::forward<Args>(rest)...));
    }
}

#endif // GENIC_FUNCTION_H_

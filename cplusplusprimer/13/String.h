/*
 * =====================================================================================
 *
 *       Filename:  String.h
 *
 *    Description:  class String
 *
 *        Version:  1.0
 *        Created:  2016年01月18日 19时27分09秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef STRING_H_
#define STRING_H_

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <initializer_list>
using std::cout;
using std::endl;
using std::allocator;
using std::string;
using std::pair;
using std::initializer_list;

class String
{
public:
    String(): elements(nullptr), end(nullptr) {}
    String(const char *);
    String(const String &);
    String(String &&) noexcept;
    String& operator= (const String &);
    String& operator= (String &&) noexcept;
    ~String();

    size_t size() const
    {
        return end - elements;
    }

    const char *c_str() const
    {
        return elements;
    }

    size_t length() const
    {
        return end - elements - 1;
    }

    void debug() const
    {
        for (auto iter = elements; iter != end; ++iter)
            cout << *iter;
        cout << endl;
    }
private:
    void free();
    pair<char *, char *> alloc_n_copy(const char *, const char *);
    void range_init(const char *, const char *);
private:
    char *elements;
    char *end;
    allocator<char> alloc;
};

#endif // STRING_H_

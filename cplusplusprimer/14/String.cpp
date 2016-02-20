/*
 * =====================================================================================
 *
 *       Filename:  String.cpp
 *
 *    Description:  class string
 *
 *        Version:  1.0
 *        Created:  2016年01月18日 19时44分32秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <initializer_list>
#include <algorithm>
#include <cstring>
#include <vector>
using std::allocator;
using std::string;
using std::pair;
using std::initializer_list;
using std::uninitialized_copy;
using std::vector;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include "String.h"

String::String(const char *s)
{
    int len = std::strlen(s);
    range_init(s, s + len + 1);
    cout << "String(const char *)" << endl;
}

String::String(const String &rhs)
{
    range_init(rhs.elements, rhs.end);
    cout << "String(const String &)" << endl;
}

String::String(String &&s) noexcept :
    elements(s.elements), end(s.end)
{
    cout << "String(String &&)" << endl;
    s.elements = s.end = nullptr;
}

String::~String()
{
    free();
    cout << "~String()" << endl;
}

String& String::operator= (const String &rhs)
{
    auto newstr = alloc_n_copy(rhs.elements, rhs.end);
    free();
    elements = newstr.first;
    end = newstr.second;
    cout << "String& operator= (const String &)" << endl;
    return *this;
}

String& String::operator= (String &&rhs) noexcept
{
    if (this != &rhs)
    {
        cout << "String& operator= (String &&) noexcept" << endl;
        free();
        elements = rhs.elements;
        end = rhs.end;
        rhs.elements = rhs.end = nullptr;
    }
    return *this;
}

pair<char *, char *> String::alloc_n_copy(const char *b, const char *e)
{
    auto str = alloc.allocate(e - b); 
    return { str, uninitialized_copy(b, e, str)};
}

void String::range_init(const char *b, const char *e)
{
    auto newstr = alloc_n_copy(b, e);
    elements = newstr.first;
    end = newstr.second;
}

void String::free()
{
    if (elements)
    {
        std::for_each(elements, end, [this](char &c) { alloc.destroy(&c); });
        alloc.deallocate(elements, end - elements);
    }
}

// istream& operator>> (istream &is, String &s)
// {
//     return is;
// }

ostream& operator<< (ostream &os, const String &s)
{
    os << s.elements;
    return os;
}

void String::operator+= (const String &rhs)
{ 
    auto str = alloc.allocate(length() + rhs.length() + 1);
    uninitialized_copy(elements, end - 1, str);
    auto new_end = uninitialized_copy(rhs.elements, rhs.end, str + length());
    free();
    elements = str;
    end = new_end;

}

String operator+ (const String &lhs, const String &rhs)
{
    String s = lhs;
    s += rhs;
    return s;
}

bool operator== (const String &lhs, const String &rhs)
{
    return strcmp(lhs.elements, rhs.elements) == 0;
}

bool operator!= (const String &lhs, const String &rhs)
{
    return !(lhs == rhs);
}

bool operator< (const String &lhs, const String &rhs)
{ 
    return strcmp(lhs.elements, rhs.elements) < 0;
}

bool operator<= (const String &lhs, const String &rhs)
{
    return !(rhs > lhs);
}

bool operator> (const String &lhs, const String &rhs)
{
    return rhs < lhs;
}

bool operator>= (const String &lhs, const String &rhs)
{
    return !(lhs < rhs);
}

// int main()
// {
//     String s("MY String+");
//     String s2("-String end");
//     String ss = s + s2;
//     cout << ss << " " << ss.length() << " " << ss.size() << endl;
// }

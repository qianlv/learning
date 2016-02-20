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


void foo(String x)
{
}
 
void bar(const String& x)
{
}
 
String baz()
{
    String ret("world");
    return std::move(ret);
}

int main()
{
    cout << "++++" << endl; 
    String vvv = baz();
    //vvv = baz();
    vvv.debug();
    cout << "++++" << endl;
    String t("test"), v(t), vv;
    vv = v;
    t.debug();

    String s0;
    String s1("hello");
    String s2(s0);
    String s3 = s1;
    s2 = s1;

    foo(s1);
    bar(s1);
    foo("temporary");
    bar("temporary");
    String s4 = baz();

    cout << "----" << endl;
    std::vector<String> svec;
    svec.push_back(s0);
    cout << "---1" << endl;
    svec.push_back(s1);
    cout << "---2" << endl;
    svec.push_back(baz());
    cout << "---3" << endl;
    svec.push_back("good job");
    cout << "---4" << endl;
    svec.push_back("good job");
    cout << "---5" << endl;
    cout << "----" << endl;
}

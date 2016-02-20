/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Main
 *
 *        Version:  1.0
 *        Created:  2016年02月18日 14时35分58秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "str_vec.h"
#include "blob.h"
#include "blobptr.h"
#include "String.h"

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
    StrBlob sb({"a", "be"}), sb2({"ab", "be"});
    cout << (sb == sb2) << endl;

    StrBlobPtr p(sb);
    ConstStrBlobPtr cp(sb);
    *p = "okey";
    cout << "StrBlobPtr operator-> " << p->size() << endl;
    cout << "StrBlobPtr operator* " << (*p).size() << endl;
    cout << "ConstStrBlobPtr operator-> " << cp->size() << endl;
    cout << "ConstStrBlobPtr operator* " << (*cp).size() << endl;

    StrVec svec = {"helo", "word", "one", "two"};
    StrVec svec2 = {"helo", "word", "one", "two"};
    StrVec svec3 = {"helo", "word", "one"};
    StrVec svec4 = {"aaa", "word", "one", "two"};
    cout << (svec == svec2) << endl;
    cout << "(svec < svec2)" << (svec < svec2) << endl;
    cout << "(svec2 < svec)" << (svec2 < svec) << endl;
    cout << "(svec < svec3)" << (svec < svec3) << endl;
    cout << "(svec3 < svec)" << (svec3 < svec) << endl;
    cout << "(svec4 < svec)" << (svec4 < svec) << endl;
    cout << "(svec < svec4)" << (svec < svec4) << endl;

    for (auto iter = sb.begin(); iter != sb.end(); iter++)
    {
        cout << iter.deref() << endl;
    }

    for (auto iter = sb.begin(); iter != sb.end(); ++iter)
    {
        cout << iter.deref() << endl;
    }

    cout << (sb.begin() + 1).deref() << endl;
    cout << (sb.end() - 1).deref() << endl;
    for (size_t i = 0; i < sb.size(); ++i)
    {
        cout << sb[i] << endl;
    }

    String s("a String+");
    String s2("string end");
    string ss("a String+");
    string ss2("String end");
    ss[0] = 'v';
    s[0] = 'v';
    cout << (s < s2) << " " << (ss < ss2) << endl;
}

/*
 * =====================================================================================
 *
 *       Filename:  ref_return.cpp
 *
 *    Description:  函数返回值 
 *
 *        Version:  1.0
 *        Created:  2015年12月11日 15时00分38秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

// 返回左值
char &get_val(string &str, string::size_type ix)
{
    return str[ix];
}

int arr[3][10] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
    {3, 4, 5, 6, 7, 8, 9, 10, 11, 12}
};

using arrT = int[10];
arrT* func1(int i)
{
    return &arr[i];
}

int (*func2(int i)) [10]
{
    return &arr[i];
}

auto func(int i) -> int(*)[10]
{
    return &arr[i];
}

int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};
decltype(odd) *arrPtr(int i)
{
    return (i % 2) ? &odd : &even;
}

decltype(odd) &arrRef(int i)
{
    return (i % 2) ? odd : even;
}


typedef string sarr[10];
string (&ref(int i))[10];
sarr &ref1(int);
auto ref2(int) -> string(&)[10];
string arrS[10];
decltype(arrS)& ref3(int i);

int main()
{
    string s("a value");
    cout << s << endl;
    get_val(s, 0) = 'A';
    cout << s << endl;
    arrT *res1 = func1(0);
    arrT *res2 = func1(1);
    arrT *res3 = func1(2);
    cout << *res1[0] << " " << *res2[0] << " " << *res3[0] << endl;
    cout << *arrPtr(1)[0] << " " << *arrPtr(2)[0] << endl;
    return 0;
}

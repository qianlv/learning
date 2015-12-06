/*
 * =====================================================================================
 *
 *       Filename:  type.cpp
 *
 *    Description:  type
 *
 *        Version:  1.0
 *        Created:  2015年12月02日 14时12分45秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

int main()
{
    typedef char *pstring;
    char s = 'a';
    char *v = new char[10];
    for (int i = 0; i < 9; ++i)
        v[i] = 'a';
    v[9] = 0;
    char * const ss = v;
    const pstring cstr = &s;
    const pstring * ps = &ss;
    (*ps)[3] = 'b';
    std::cout << cstr << std::endl;
    std::cout << *ps << std::endl;

    // auto
    // auto 以引用对象的类型为auto的类型 
    int i = 0, &r = i;
    auto a = r;
    a = 42; r = 7;
    std::cout << i << " " << r << " " << a << std::endl;

    // auto 一般忽略顶层const
    const int ci = i, &cr = ci;
    auto b = ci; // b 是一个整数 ci的顶层const被忽略.
    b = 42;
    auto c = cr; // 同上
    c = 42;
    auto d = &i; // 整型指针
    // d = 42; 错误 int -> int *
    auto e = &ci; // 整形常量的指针 
    // e = 42; 错误 int -> const int *

    // 推断出顶层const
    const auto f = ci;
    
    // 引用类型设为auto
    auto &g = ci;
    // const auto &g1 = ci;
    // const int &g2 = ci;
    // auto &h = 42; // 错误:不能为非常量引用绑定字面值
    const auto &j = 42;
    std::cout << b << " " << c << " " << d << " " << e << " " << f << " "
              << g << " " << j << " " << std::endl;

    auto &n = i;
    // auto *p2 = &ci; 错误&ci类型是const int
    const auto *p2 = &ci;
    std:: cout << n << " " << *p2 << std::endl;

    // decltype 返回变量的类型(包括顶层const和引用在内)
    const int &cj = ci; 
    decltype(ci) x = 0; // const int
    decltype(cj) y = x; // const int &
    // decltype(cj) z;     //  错误 z 是一个引用, 必须初始化
    std::cout << x << " " << y << std::endl;

    // decltype 与 引用
    int ii = 42, *p = &ii, &rr = ii;
    decltype(rr + 0) bb; // int
    bb = 1024;
    // decltype(*p) cc;    // 如果表达式的内容是解引用, 则 decltype 是引用类型, cc: int&, 必须初始化
    std::cout << ii << " " << *p << " " << rr << " " << bb << std::endl;
    // decltype ((variable)) 结果永远是引用
    // decltype ((ii)) dd; // dd: int&, 必须初始化
    decltype (ii) ee = 0;  // ee: int
    std::cout << ee << std::endl;
}



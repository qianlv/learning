/*
 * =====================================================================================
 *
 *       Filename:  2_36_37_38.cpp
 *
 *    Description:  2.36
 *
 *        Version:  1.0
 *        Created:  2015年12月02日 17时14分29秒 CST
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
    // 2.36
    int a = 3, b = 4;
    decltype (a) c = a; // int
    decltype ((b)) d = a; // int&
    ++c;
    ++d;
    std::cout << a << " " << b << " " << c << " " << d << std::endl;

    // 2.37
    // 表达式i=x的类型是int&
    decltype (a) cc = a; // int
    decltype (a = b) dd = a; // int&
    ++cc;
    ++dd;
    std::cout << a << " " << b << " " << cc << " " << dd << std::endl;

    // 2.38
    int i = 1, &j = i;
    decltype (i) ii = i;
    auto iii = i;
    std::cout << i << " " << ii << " " << iii << std::endl;
    decltype (j) jj = a;
    auto jjj = a;
    ++jj;
    jjj += 10;
    std::cout << a << " " << jj << " " << jjj << std::endl;
}

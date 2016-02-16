/*
 * =====================================================================================
 *
 *       Filename:  13_17_3.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年01月10日 17时21分56秒 CST
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

class Numbered
{
public:
    Numbered() 
    {
        mysn = unique++;
    }

    Numbered(const Numbered &n)
    {
        mysn = unique++;
    }

    int mysn;
    static int unique;
};

int Numbered::unique = 7;

void f(const Numbered s)
{
    cout << s.mysn << endl;
}
int main()
{
    Numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
}

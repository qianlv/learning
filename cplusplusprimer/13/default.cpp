/*
 * =====================================================================================
 *
 *       Filename:  default.cpp
 *
 *    Description:  default function
 *
 *        Version:  1.0
 *        Created:  2016年01月10日 22时47分51秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cout;
using std::endl;

class F
{
public:
    F() = default;
    //F(): F(110) {}
    F(int b): a(b) {}
    void print() const
    {
        cout << "F : " << a << endl;
    }
private:
    int a;
};

class FF
{
public:
    FF() = default;
    //FF(): FF(F(1), F(2)) {}
    FF(class F f1, class F rf) : f(f1), rf(rf)
    {
    }
    void print()
    {
        cout << "FF : " << endl;
        f.print();
        rf.print();
    }
    // FF& operator= (const FF& ff) = default;
    // {
    //     f = ff.f;
    //     rf = ff.rf;
    //     return *this;
    // }
private:
    class F f;
    class F rf;
};

int main()
{
    FF ff, ff2;
    // ff2 = ff;
    ff2.print();
}

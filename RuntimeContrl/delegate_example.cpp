// =====================================================================================
// 
//       Filename:  delegate_example.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  11/12/2014 04:00:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  肖守冬, qianlv7@qq.com
//        License:  Copyright © 2014 肖守冬. All Rights Reserved.
// 
// =====================================================================================

#include "delegate_example.h"
void printA(int a, int b)
{
    std::cout << a + b << std::endl;
}
void print_s(int a)
{
    std::cout << "on print_s: " << a << std::endl;
}

class s_class
{
public:
    static void printC(int a, int b)
    {
        std::cout << " On s_class: " << a + b << std::endl;
    }
    static Delegate<boost::function<void (int) > > &getDelegate()
    {
        return s_class_delegate;
    }
private:
    static Delegate<boost::function<void (int) > > s_class_delegate;
};
Delegate<boost::function<void (int) > > s_class::s_class_delegate;

class base
{
public:
    typedef Delegate<boost::function<void (int, int) > > Delegate2;
    void printB(int a, int b)
    {
        std::cout << a + b << std::endl;
    }
    void print_s(int a)
    {
        std::cout << "on base print_s: " << a << std::endl;
    }
    void invoke(int a, int b)
    {
        boost::function<void (int)> tmp = boost::bind(&base::print_s, this, _1);
        (s_class::getDelegate()).add(&tmp);
        boost::function<void (int, int) > it = boost::bind(&base::printB, this, _1, _2);
        ievent += &it;
        ievent(a, b);
    }
private:
    Delegate2 ievent;
};


int main()
{
    typedef Delegate<boost::function<void (int, int)> > Delegate2;
    typedef Delegate2::DelegateType Delegate2Type;
    Delegate2 ievent;
    Delegate2Type delegate = boost::bind(&printA, _1, _2);
    base b; 
    Delegate2Type delegate2 = boost::bind(&base::printB, b, _1, _2);
    ievent += &delegate;
    ievent += &delegate2;
    ievent(10, 20);
    b.invoke(2, 3);
    (s_class::getDelegate())(1000);
}

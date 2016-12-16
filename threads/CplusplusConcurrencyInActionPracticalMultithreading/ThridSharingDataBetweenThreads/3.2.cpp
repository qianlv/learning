/*
 * =====================================================================================
 *
 *       Filename:  3.2.cpp
 *
 *    Description:  Accidentally passing out a reference to prctected data
 *
 *        Version:  1.0
 *        Created:  2016年12月15日 14时22分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <list>
#include <mutex>
#include <string>

class some_data
{
    int a;
    std::string b;
public:
    void do_something();
};

class data_wrapper
{
private:
    some_data data;
    std::mutex m;
public:
    template <typename Function>
    void process_data(Function func)
    {
        std::lock_guard<std::mutex> l(m);
        func(data); // 把保护的数据传递给用户定义的函数, 导致不可预知的问题.
    }
};

some_data* unprotectd;
void malicious_function(some_data& protected_data)
{
    unprotectd = &protected_data;
}

data_wrapper x;

void foo()
{
    x.process_data(malicious_function);
    unprotectd->do_something();
}

/*
 * =====================================================================================
 *
 *       Filename:  2.1.cpp
 *
 *    Description:  A function that returns while a thread still has access to local variables
 *
 *        Version:  1.0
 *        Created:  2016年12月14日 19时05分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <thread>

void do_someting(int) { }

struct func {
    int &i;
    func (int &i_) : i(i_) {}
    void operator() ()
    {
        for (unsigned j = 0; j < 100000; ++j)
        {
            do_someting(j);
        }
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();     // not wait
    // my_thread.join();
}

int main(void)
{
    oops();
    return 0;
}

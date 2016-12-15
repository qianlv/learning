/*
 * =====================================================================================
 *
 *       Filename:  2.3.cpp
 *
 *    Description:  using RAII to wait for a thread to complete
 *
 *        Version:  1.0
 *        Created:  2016年12月14日 19时17分28秒
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

class thread_guard
{
public:
    thread_guard(std::thread& t_) : t(t_) {}
    ~thread_guard()
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    thread_guard(const thread_guard&) = delete;
    thread_guard& operator=(const thread_guard&) = delete;
private:
    std::thread& t;
};

void do_someting_in_current_thread() {}
void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    do_someting_in_current_thread();
}


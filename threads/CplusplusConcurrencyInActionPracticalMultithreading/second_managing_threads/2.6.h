/*
 * =====================================================================================
 *
 *       Filename:  2.6.cpp
 *
 *    Description:  using RAII to wait for a thread to complete
 *
 *        Version:  1.0
 *        Created:  2016年12月14日 21时10分02秒
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

class scoped_thread
{
public:
    explicit scoped_thread(std::thread t_) : t(std::move(t_))
    {
        if (!t.joinable())
        {
            throw std::logic_error("No thread");
        }
    }
    ~scoped_thread()
    {
        t.join();
    }
    scoped_thread(const scoped_thread&) = delete;
    scoped_thread& operator=(const scoped_thread&) = delete;
private:
    std::thread t;
};

/*
 * =====================================================================================
 *
 *       Filename:  rw_lock.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月18日 15时03分28秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef RW_LOCK_
#define RW_LOCK_ 

#include <pthread.h>
#include <boost/noncopyable.hpp>

#include "mutex.h"
#include "condition.h"

class RwLock : public boost::noncopyable
{
public:
    RwLock() :
        readers(0), writers(0),
        wait_readers(0), wait_writers(0),
        mutex_(), read_cond_(mutex_), write_cond_(mutex_)
    {
    }

    void RLock()
    {
        MutexLockGuard lock(mutex_);
        if (writers > 0 || wait_writers > 0)
        {
            ++wait_readers;
            while (writers > 0 || wait_writers > 0)
                read_cond_.Wait();
            --wait_readers;
        }
        ++readers;
    }

    void RUnLock()
    {
        MutexLockGuard lock(mutex_);
        --readers;
        if (wait_writers && readers == 0)
            write_cond_.Notify();
    }

    void WLock()
    {
        MutexLockGuard lock(mutex_);
        if (writers > 0 || readers > 0)
        {
            ++wait_writers;
            while (writers > 0 || readers > 0)
                write_cond_.Wait();
            --wait_writers;
        }
        writers = 1;
    }

    void WUnLock()
    {
        MutexLockGuard lock(mutex_);
        writers = 0;
        if (wait_writers > 0)
            write_cond_.Notify();
        else if (wait_readers > 0)
            read_cond_.NotifyAll();
    }

private:
    unsigned readers, writers, wait_readers, wait_writers;
    MutexLock mutex_;
    Condition read_cond_, write_cond_;
};


class RwLock_Two_Mutex : public boost::noncopyable
{
public:
    RwLock_Two_Mutex() : readers(0), read_mutex_(), write_mutex_()
    {
    }

    void RLock()
    {
        MutexLockGuard lock(read_mutex_);
        if (++readers == 1)
            write_mutex_.Lock();
    }

    void RUnLock()
    {
        MutexLockGuard lock(read_mutex_);
        if (--readers == 0)
            write_mutex_.Unlock();
    }

    void WLock()
    {
        write_mutex_.Lock();
    }

    void WUnLock()
    {
        write_mutex_.Unlock();
    }

private:
    unsigned readers;
    MutexLock read_mutex_, write_mutex_;
};

#endif /* ifndef RW_LOCK_ */

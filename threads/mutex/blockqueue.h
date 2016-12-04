/*
 * =====================================================================================
 *
 *       Filename:  blockqueue.h
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  2016年06月18日 15时59分44秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BLOCK_QUEUE
#define BLOCK_QUEUE 

#include <iostream>
#include <pthread.h>
#include <queue>
#include <boost/noncopyable.hpp>
#include <assert.h>

#include "mutex.h"
#include "condition.h"

template <typename T>
class BlockQueue : public boost::noncopyable
{
public:
    BlockQueue() : mutex_(), noEmpty_(mutex_), que_()
    {
    }

    void put(const T& x)
    {
        MutexLockGuard lock(mutex_);
        que_.push(x);
        noEmpty_.Notify();
    }

    void put(T&& x)
    {
        MutexLockGuard lock(mutex_);
        que_.push(std::move(x));
        noEmpty_.Notify();
    }

    T get()
    {
        MutexLockGuard lock(mutex_);
        while (que_.empty())
            noEmpty_.Wait();
        assert(!que_.empty());

        T front(std::move(que_.front()));
        que_.pop();
        return front;
    }

    size_t size() const
    {
        MutexLockGuard lock(mutex_);
        return que_.size();
    }
private:
    mutable MutexLock mutex_;
    Condition noEmpty_;
    std::queue<T> que_;
};

#endif /* ifndef BLOCK_QUEUE */

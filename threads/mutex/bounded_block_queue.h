/*
 * =====================================================================================
 *
 *       Filename:  bounded_block_queue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年06月18日 16时42分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BOUNDED_BLOCK_QUEUE
#define BOUNDED_BLOCK_QUEUE 

#include <boost/circular_buffer.hpp>
#include <pthread.h>
#include <boost/noncopyable.hpp>
#include <assert.h>

#include "mutex.h"
#include "condition.h"

template <typename T>
class BoundedBlockQueue : public boost::noncopyable
{
public:
    BoundedBlockQueue(int maxSize) : mutex_(), noEmpty_(mutex_), noFull_(mutex_), que_(maxSize)
    {
    }

    void put(const T& x)
    {
        MutexLockGuard lock(mutex_); 
        while (que_.full())
            noFull_.Wait();
        assert(!que_.full());
        que_.push_back(x);
        noEmpty_.Notify();
    }

    T get()
    {
        MutexLockGuard lock(mutex_); 
        while (que_.empty())
            noEmpty_.Wait();
        assert(!que_.empty());
        T front(que_.front());
        que_.pop_front();
        noFull_.Notify();
        return front;
    }

    bool empty() const
    {
        MutexLockGuard lock(mutex_); 
        return que_.empty();
    }

    bool full() const
    {
        MutexLockGuard lock(mutex_);
        return que_.full();
    }

    size_t size() const
    {
        MutexLockGuard lock(mutex_);
        return que_.size();
    }

    size_t capacity() const
    {
        MutexLockGuard lock(mutex_);
        return que_.capacity();
    }

private:
    /* data */
    mutable MutexLock mutex_;
    Condition noEmpty_;
    Condition noFull_;
    boost::circular_buffer<T> que_;
};


#endif /* ifndef BOUNDED_BLOCK_QUEUE */


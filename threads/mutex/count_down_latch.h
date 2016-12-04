/*
 * =====================================================================================
 *
 *       Filename:  count_down_latch.h
 *
 *    Description:  CountDownLatch
 *
 *        Version:  1.0
 *        Created:  2016年04月09日 22时09分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef COUNT_DOWN_LATCH_H_
#define COUNT_DOWN_LATCH_H_

#include "mutex.h"
#include "condition.h"

#include <pthread.h>
#include <boost/noncopyable.hpp>

class CountDownLatch : public boost::noncopyable
{
public:
    explicit CountDownLatch(int count):
        mutex_(),
        condition_(mutex_),
        count_(count)
    {
    }

    void wait()
    {
        MutexLockGuard lock(mutex_);
        while (count_ > 0)
            condition_.Wait();
    }

    void CountDown()
    {
        MutexLockGuard lock(mutex_);
        --count_;
        if (count_ == 0)
            condition_.NotifyAll();
    }

    int GetCount() const
    {
        MutexLockGuard lock(mutex_);
        return count_;
    }
private:
    mutable MutexLock mutex_;
    Condition condition_;
    int count_;
};

#endif // COUNT_DOWN_LATCH_H_

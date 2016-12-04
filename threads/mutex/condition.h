/*
 * =====================================================================================
 *
 *       Filename:  condition.h
 *
 *    Description:  条件变量
 *
 *        Version:  1.0
 *        Created:  2016年04月09日 19时56分33秒
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef CONDITION_H_
#define CONDITION_H_

#include "mutex.h"

#include <pthread.h>
#include <boost/noncopyable.hpp>


class Condition : public boost::noncopyable
{
public:
    explicit Condition(MutexLock &mutex) : mutex_(mutex)
    {
        pthread_cond_init(&gcond_, NULL);
    }

    ~Condition()
    {
        pthread_cond_destroy(&gcond_);
    }
    
    void Wait()
    {
        pthread_cond_wait(&gcond_, mutex_.GetPthreadMutex());
    }

    void Notify()
    {
        pthread_cond_signal(&gcond_);
    }

    void NotifyAll()
    {
        pthread_cond_broadcast(&gcond_);
    }

private:
    pthread_cond_t gcond_;
    MutexLock &mutex_;
};

#endif // CONDITION_H_

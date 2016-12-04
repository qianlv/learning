/*
 * =====================================================================================
 *
 *       Filename:  mutex.h
 *
 *    Description:  封装Mutex
 *
 *        Version:  1.0
 *        Created:  2016年04月09日 18时26分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>
#include <assert.h>
#include <boost/noncopyable.hpp>

struct MutexAttr
{
    MutexAttr()
    {
        pthread_mutexattr_init(&attr);
    }

    ~MutexAttr()
    {
        pthread_mutexattr_destroy(&attr);
    }
    
    void set_normal()
    {
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
    }

    void set_errorcheck()
    {
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    }

    void set_recursive()
    {
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    }
    
    pthread_mutexattr_t attr;
};

class MutexLock : boost::noncopyable
{
public:
    MutexLock()
    {
        MutexAttr attr;
        attr.set_normal();
        pthread_mutex_init(&mutex_, &attr.attr);
    }

    ~MutexLock()
    {
        pthread_mutex_destroy(&mutex_);
    }

    void Lock()
    {
        pthread_mutex_lock(&mutex_);
    }

    void Unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }

    pthread_mutex_t* GetPthreadMutex()
    {
        return &mutex_;
    }
private:
    pthread_mutex_t mutex_;
};

class MutexLockGuard : public boost::noncopyable
{
public:
    explicit MutexLockGuard(MutexLock &mutex) : mutex_(mutex)
    {
        mutex_.Lock();
    }

    ~MutexLockGuard()
    {
        mutex_.Unlock();
    }

private:
    MutexLock &mutex_;
};

/* MutexLockGuard(mutex); 遗漏变量名, 产生一个临时对象又马上销毁, 没有锁住临界区. */
#define MutexLockGuard(x) static_assert(false, "missing mutex guard var name")

#endif // MUTEX_H_

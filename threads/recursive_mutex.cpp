/*
 * =====================================================================================
 *
 *       Filename:  recursive_mutex.cpp
 *
 *    Description:  使用递归 mutex.
 *
 *        Version:  1.0
 *        Created:  2016年03月30日 14时30分48秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#include "thread_attr.h"

struct to_info
{
    void            (*to_fn)(void *);
    void             *to_arg;
    struct timespec   to_wait;
};

const int SECTONSEC(1000000000);

#if !defined(CLOCK_REALTIME) || defined(BSD)
#define clock_nanosleep(ID, FL, REQ, REM)   nanosleep((REQ), (REM))
#endif

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#define USECTONSEC 1000

void clock_gettime(int id, struct timespec *tsp)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    tsp->tv_sec = tv.tv_sec;
    tsp->tv_nsec = tv.tv_usec * USECTONSEC;
}

#endif // CLOCK_REALTIME

void *timeout_helper(void *arg)
{
    struct to_info *tip = static_cast<struct to_info *>(arg);
    clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);
    (*tip->to_fn)(tip->to_arg);
    free(arg);
    return static_cast<void *>(0);
}

void timeout(const struct timespec *when, void (*func)(void *), void *arg)
{
    struct timespec now;
    struct to_info *tip = NULL;
    int             err;

    clock_gettime(CLOCK_REALTIME, &now);

    if ((when->tv_sec > now.tv_sec) ||
        (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec))
    {
        tip = static_cast<struct to_info*>(malloc(sizeof(struct to_info)));
        if (tip != NULL)
        {
            tip->to_fn  = func;
            tip->to_arg = arg;
            tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
            if (when->tv_nsec >= now.tv_nsec)
            {
                tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
            }
            else
            {
                tip->to_wait.tv_sec--;
                tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
            }
            err = makethread(timeout_helper, (void *)tip);
            if (err == 0)
                return;
            else
                free(tip);
        }
    }
    /*
     * when when <= now, malloc fail or can't make a thread, we just call the function now.
     * */
    (*func)(arg);
}

pthread_mutexattr_t attr;
pthread_mutex_t mutex;

void retry(void *arg)
{
    pthread_mutex_lock(&mutex);
    std::cout << "arg = " << (unsigned long)arg << std::endl;
    pthread_mutex_unlock(&mutex);
}

int main()
{
    int err, condition, arg;
    struct timespec when;
    if ((err = pthread_mutexattr_init(&attr)) != 0)
    {
        std::cerr << "pthread_mutexattr_init fail" << strerror(errno) << std::endl;
        return -1;
    }

    if ((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0)
    {
        std::cerr << "can't set recursive type" << strerror(errno) << std::endl;
        return -1;
    }

    if ((err = pthread_mutex_init(&mutex, &attr)) != 0)
    {
        std::cerr << "can't create recursive mutex" << strerror(errno) << std::endl;
        return -1;
    }
    
    condition = 1;
    arg = 2;
    pthread_mutex_lock(&mutex);
    if (condition)
    {
        clock_gettime(CLOCK_REALTIME, &when);
        when.tv_sec += 2;
        timeout(&when, retry, (void *)((unsigned long)arg));
    }
    pthread_mutex_unlock(&mutex);
    sleep(3);
    return 0;
}


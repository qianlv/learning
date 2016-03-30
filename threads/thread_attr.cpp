/*
 * =====================================================================================
 *
 *       Filename:  thread_attr.cpp
 *
 *    Description:  线程属性
 *
 *        Version:  1.0
 *        Created:  2016年03月30日 14时29分06秒 CST
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
#include <pthread.h>
#include <string.h>

int makethread(void *(*fn)(void *), void *arg)
{
    int             err;
    pthread_t       tid;
    pthread_attr_t  attr;
    err = pthread_attr_init(&attr);
    if (err != 0)
    {
        std::cerr << "pthread_attr init fail: " << strerror(errno) << std::endl;
        return err;
    }

    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err == 0)
    {
        err = pthread_create(&tid, &attr, fn, arg);
    }
    pthread_attr_destroy(&attr);
    return err;
}

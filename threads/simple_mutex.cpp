/*
 * =====================================================================================
 *
 *       Filename:  simple_mutex.cpp
 *
 *    Description:  Simple Mutex Lock Example
 *
 *        Version:  1.0
 *        Created:  2016年03月28日 22时19分22秒 CST
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

struct foo
{
    int             f_count;
    pthread_mutex_t f_lock;
};

struct foo * foo_alloc()
{
    struct foo *fp = new foo;
    fp->f_count = 1;
    if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
    {
        delete fp;
        return NULL;
    }
    return (fp);
}

void foo_hold(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    if (--fp->f_count == 0)
    {
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        delete fp;
    } else
    {
        pthread_mutex_unlock(&fp->f_lock);
    }
}

int main()
{
    return 0;
}

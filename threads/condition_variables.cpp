/*
 * =====================================================================================
 *
 *       Filename:  condition_variables.cpp
 *
 *    Description:  条件变量
 *
 *        Version:  1.0
 *        Created:  2016年03月29日 19时55分46秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <pthread.h>

#include <iostream>
#include <vector>
#include <string>

struct msg
{
    struct msg *m_next;
    int val;
};

struct msg *workq = NULL;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg()
{
    struct msg *mp;
    for ( ;; )
    {
        pthread_mutex_lock(&qlock);
        while (workq == NULL)
            pthread_cond_wait(&qready, &qlock);
        mp = workq;
        workq = mp->m_next;
        std::cout << mp->val << std::endl;
        pthread_mutex_unlock(&qlock);
    }
}

void enqueue_msg(struct msg *mp)
{
    pthread_mutex_lock(&qlock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
}

void* worker(void *flag)
{
    process_msg();
    return static_cast<void *>(0);
}


int main()
{
    std::vector<pthread_t> ptid_list;
    for (int i = 0; i < 10; ++i)
    {
        pthread_t tid;
        int err = pthread_create(&tid, NULL, worker, (void *)(NULL));
        if (err != 0)
        {
            exit(1);
        }
        ptid_list.push_back(tid);
    }

    for (int i = 0; i < 100; ++i)
    {
        struct msg *mp = new msg;
        mp->val = i;
        enqueue_msg(mp);
    }

    for (auto iter = ptid_list.begin(); iter != ptid_list.end(); ++iter)
    {
        pthread_join(*iter, NULL);
    }
    
}

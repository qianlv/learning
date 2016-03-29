/*
 * =====================================================================================
 *
 *       Filename:  read_write_lock.cpp
 *
 *    Description:  读写锁
 *
 *        Version:  1.0
 *        Created:  2016年03月29日 10时00分43秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <iostream>
#include <vector>

struct job
{
    struct job *j_next;
    struct job *j_prev;
    pthread_t   j_id;
};

struct queue
{
    struct job       *q_head;
    struct job       *q_tail;
    pthread_rwlock_t  q_lock;
};

int queue_init(struct queue *qp)
{
    int err;

    qp->q_head = NULL;
    qp->q_tail = NULL;
    err = pthread_rwlock_init(&qp->q_lock, NULL);
    if (err != 0)
        return (err);
    return 0;
}

void job_insert(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = qp->q_head;
    jp->j_prev = NULL;
    if (qp->q_head != NULL)
    {
        qp->q_head->j_prev = jp;
    }
    else
    {
        qp->q_tail = jp;
    }
    qp->q_head = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

void job_append(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->q_lock);
    jp->j_next = NULL;
    jp->j_prev = qp->q_tail;
    if (qp->q_tail != NULL)
    {
        qp->q_tail->j_next = jp;
    }
    else
    {
        qp->q_head = jp;
    }
    qp->q_tail = jp;
    pthread_rwlock_unlock(&qp->q_lock);
}

void job_remove(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->q_lock);
    if (jp == qp->q_head)
    {
        qp->q_head = jp->j_next;
        if (qp->q_tail == jp)
            qp->q_tail = NULL;
        else
            jp->j_next->j_prev = jp->j_prev;
    }
    else if (jp == qp->q_tail)
    {
        qp->q_tail = jp->j_prev;
        jp->j_prev->j_next = jp->j_next;
    }
    else
    {
        jp->j_prev->j_next = jp->j_next;
        jp->j_next->j_prev = jp->j_prev;
    }
    pthread_rwlock_unlock(&qp->q_lock);
}

struct job * job_find(struct queue *qp, pthread_t id)
{
    struct job *jp;
    if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
    {
        return NULL;
    }

    for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
    {
        if (pthread_equal(jp->j_id, id))
            break;
    }
    pthread_rwlock_unlock(&qp->q_lock);
    return (jp);
}

void* worker(void *qp)
{
    pthread_t tid = pthread_self();
    printf("%lu\n", (unsigned long)tid);
    struct job *jb = NULL;
    while (jb == NULL)
    {
        jb = job_find((struct queue*)qp, tid);
    }
    printf("worker thread %lu (0x%lx)\n", (unsigned long)tid, (unsigned long)(jb->j_id));
    job_remove((struct queue *)qp, jb);
    return (void *)0;
}

int main()
{
    struct queue *qp = new queue;
    queue_init(qp);
    std::vector<pthread_t> ptid_list;
    for (int i = 0; i < 10; ++i)
    {
        pthread_t tid;
        int err = pthread_create(&tid, NULL, worker, (void *)qp);
        if (err != 0)
        {
            exit(1);
        }
        struct job *jb = new job;
        jb->j_next = jb->j_prev = NULL;
        jb->j_id = tid;
        job_append(qp, jb);
        ptid_list.push_back(tid);
    }
    for (auto iter = ptid_list.begin(); iter != ptid_list.end(); ++iter)
    {
        pthread_join(*iter, NULL);
    }
}

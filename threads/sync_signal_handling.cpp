/*
 * =====================================================================================
 *
 *       Filename:  sync_signal_handling.cpp
 *
 *    Description:  同步信号处理
 *
 *        Version:  1.0
 *        Created:  2016年04月06日 15时06分25秒 CST
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
#include <signal.h>

int         quitflag = 0;
sigset_t    mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitlock = PTHREAD_COND_INITIALIZER;

void* thr_fn(void *arg)
{
    int err, signo;

    for ( ; ; )
    {
        err = sigwait(&mask, &signo);
        if (err != 0)
        {
            exit(1);
        }
        switch (signo)
        {
        case SIGINT:
            std::cout << "\ninterrupt\n";
            break;
        case SIGQUIT:
            pthread_mutex_lock(&lock);
            quitflag = 1;
            pthread_mutex_unlock(&lock);
            pthread_cond_signal(&waitlock);
            return 0;
        defautl:
            std::cout << "unexcepted signal " << signo << std::endl;
            exit(1);
        }
    }
}

int main()
{
    int         err;
    sigset_t    oldmask;
    pthread_t   tid;

    sigemptyset(&mask);
    sigaddset(&maks, SIGINT);
    sigaddset(&maks, SIGQUIT);
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
    {
        std::cerr << "SIG_BLOCK error\n";
        exit(EXIT_FAILURE);
    }
    
    err = pthread_create(&tid, NULL, thr_fn, 0);
    if (err != 0)
    {
        std::cerr << "can't create thread\n";
        exit(EXIT_FAILURE);
    }

    pthread_mutex_lock(&lock);
    while (quitflag == 0)
        pthread_cond_wait(&waitlock, &lock);
    pthread_mutex_unlock(&lock);

    /* SIGQUIT has been caught and is now blocked; do whatever */
    quitflag = 0;
    
    /* reset signal mask which unblocks SIGQUIT. */
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        std::cerr << "SIG_SETMASK error\n";
        exit(EXIT_FAILURE);
    }
    return 0;
}

/*
 * =====================================================================================
 *
 *       Filename:  thread_safe_function.c
 *
 *    Description:  线程安全函数 
 *
 *        Version:  1.0
 *        Created:  2016年03月30日 22时03分36秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>

#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

extern char **environ;

pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init()
{
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    /*
     * 此处递归的目的是保证异步信号安全。
     * */
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char *name, char *buf, int buflen)
{
    int i, len, olen;

    pthread_once(&init_done, thread_init);
    len = strlen(name);
    pthread_mutex_lock(&env_mutex);
    for (i = 0; environ[i]; ++i)
    {
        if (strncmp(name, environ[i], len) == 0 &&
            (environ[i][len] == '='))
        {
            olen = strlen(&environ[i][len + 1]);
            if (olen >= buflen)
            {
                pthread_mutex_unlock(&env_mutex);
                return (ENOSPC);
            }
            strcpy(buf, &environ[i][len+1]);
            pthread_mutex_unlock(&env_mutex);
            return (0);
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return (ENOENT);
}

void *tr_fn(void *arg)
{
    char buf[100];
    getenv_r("LC_PAPER", buf, 100);
    assert(strcmp(buf, "zh_SG.UTF-8") == 0);
    //std::cout << buf << std::endl;
    return static_cast<void *>(0);
}
void *tr_fn1(void *arg)
{
    char *val = getenv("PATH");
    // std::cout << (strcmp(val, "zh_SG.UTF-8") == 0) << std::endl;
    assert(strcmp(val, "/home/qianlv/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games") == 0);
    return static_cast<void *>(0);
}

int main()
{
    std::vector<pthread_t> tids;
    for (int i = 0; i < 100; ++i)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, tr_fn1, static_cast<void *>(NULL));
        tids.push_back(tid);
    }
    for (int i = 0; i < 100; ++i)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, tr_fn, static_cast<void *>(NULL));
        tids.push_back(tid);
    }
    for (auto tid : tids)
        pthread_join(tid, NULL);
}

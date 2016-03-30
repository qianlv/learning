/*
 * =====================================================================================
 *
 *       Filename:  thread_specific_data.cpp
 *
 *    Description:  线程私有数据 
 *
 *        Version:  1.0
 *        Created:  2016年03月30日 22时38分30秒 CST
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

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

const int MAXSTRINGSZ(4096);

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void thread_init()
{
    pthread_key_create(&key, free);
}

char *getenv(const char *name)
{
    int     i, len;
    char    *envbuf;
    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);
    envbuf = (char *)pthread_getspecific(key);
    if (envbuf == NULL)
    {
        envbuf = (char *)malloc(MAXSTRINGSZ);
        if (envbuf == NULL)
        {
            pthread_mutex_unlock(&env_mutex);
            return (NULL);
        }
        pthread_setspecific(key, envbuf);
    }
    len = strlen(name);
    for (i = 0; environ[i] != NULL; ++i)
    {
        if (strncmp(name, environ[i], len) == 0 &&
           (environ[i][len] == '='))
        {
            strncpy(envbuf, &environ[i][len + 1], MAXSTRINGSZ - 1);
            pthread_mutex_unlock(&env_mutex);
            return (envbuf);
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return (NULL);
}

void *tr_fn1(void *arg)
{
    char *val = getenv("PATH");
    assert(strcmp(val, "/home/qianlv/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games") == 0);
    return static_cast<void *>(0);
}

int main()
{
    std::vector<pthread_t> tids;
    for (int i = 0; i < 10; ++i)
    {
        pthread_t tid;
        pthread_create(&tid, NULL, tr_fn1, static_cast<void *>(NULL));
        tids.push_back(tid);
    }
    for (auto tid : tids)
        pthread_join(tid, NULL);
}

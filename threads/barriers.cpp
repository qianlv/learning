/*
 * =====================================================================================
 *
 *       Filename:  barriers.cpp
 *
 *    Description:  Barries
 *
 *        Version:  1.0
 *        Created:  2016年03月29日 21时02分18秒 CST
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
#include <limits.h>
#include <sys/time.h>

#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

const int NTHR(8);
const long NUMNUM(800L);
const long THUM(NUMNUM / NTHR);

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;

void* thr_fn(void *arg)
{
    long idx = (long)arg;
    std::sort(&nums[idx], &nums[idx + THUM], std::greater<int>());

    // std::ostream_iterator<int> out_iter(std::cout, " ");
    // std::copy(&nums[idx], &nums[idx + THUM], out_iter);
    // std::cout << std::endl;
    pthread_barrier_wait(&b);
    return static_cast<void *>(0);
}

void merge()
{
    long idx[NTHR];
    long i, maxidx, sidx, num;
    for (int i = 0; i < NTHR; ++ i)
        idx[i] = i * THUM;
    for (sidx = 0; sidx < NUMNUM; sidx++)
    {
        num = LONG_MIN;
        for (i = 0; i < NTHR; ++i)
        {
            if ((idx[i] < (i + 1) * THUM) && (nums[idx[i]] > num))
            {
                num = nums[idx[i]];
                maxidx = i;  
            }
        }
        snums[sidx] = nums[idx[maxidx]];
        idx[maxidx] ++;
    }
}

int main()
{
    unsigned long i;
    struct timeval start, end;
    long long startusec, endusec;
    double elapsed;
    int err;
    pthread_t tid;

    srandom(time(NULL));
    for (i = 0; i < NUMNUM; ++i)
    {
        nums[i] = random() % NUMNUM;
    }
    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, NTHR + 1);
    for (i = 0; i < NTHR; ++i)
    {
        err = pthread_create(&tid, NULL, thr_fn, (void *)(i * THUM));
        if (err != 0)
        {
            std::cerr << "phread_create faile" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    pthread_barrier_wait(&b);
    merge();
    gettimeofday(&end, NULL);

    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = static_cast<double>(endusec - startusec) / 1000000.0;
    std::cout << "sort took " << elapsed << "seconds." << std::endl;

    std::ostream_iterator<int> out_iter(std::cout, " ");
    std::copy(std::begin(snums), std::end(snums), out_iter);
    std::cout << std::endl;

    return 0;
}



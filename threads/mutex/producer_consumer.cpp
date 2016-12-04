/*
 * =====================================================================================
 *
 *       Filename:  producer_consumer.cpp
 *
 *    Description:  生产者和消费者
 *
 *        Version:  1.0
 *        Created:  2016年06月18日 16时22分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <pthread.h>
#include <thread>
#include <vector>

#include "blockqueue.h"
#include "bounded_block_queue.h"

//BlockQueue<std::pair<std::thread::id, int>> block_queue;
BoundedBlockQueue<std::pair<std::thread::id, int>> block_queue(100);

void producer(int n)
{
    for (int i = 0; i < n; ++i) 
    {
        block_queue.put(std::make_pair(std::this_thread::get_id(), i));
    }
}

void consumer()
{
    while (true)
    {
        auto p = block_queue.get();
        std::cout << "thread id = " << p.first << " val = " << p.second << std::endl;
    }
}

int main(void)
{
    std::cout << "---" << std::endl;
    std::vector<std::thread> threads;
    for (int i = 1; i <= 10; ++i) 
    {
        threads.push_back(std::thread(producer, i * 2));
    }
    consumer();
    for (auto& th : threads) th.join();
    return 0;
}



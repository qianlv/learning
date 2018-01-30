/*
 * =====================================================================================
 *
 *       Filename:  waiting_for_data_to_process_with_a_condition_variable4.1.cpp
 *
 *    Description:  Waiting for data to process with a condition variable
 *
 *        Version:  1.0
 *        Created:  2016年12月16日 21时51分53秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

struct data_chunk {
    /* data */
};

std::mutex mut;
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

bool more_data_to_prepare();
data_chunk prepare_data();
void data_preparation_thread()
{
    while (more_data_to_prepare())
    {
        const data_chunk data = prepare_data();
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
}

void process(data_chunk);
bool is_last_chunk(data_chunk);
void data_processing_thread()
{
    while (true)
    {
        // data_chunk data;
        // {
            // std::unique_lock<std::mutex> lk(mut);
            // data_cond.wait(
                // lk, []{ return !data_queue.empty(); });
            // data = data_queue.front();
            // data_queue.pop();
        // }

        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(
            lk, []{ return !data_queue.empty(); });
        data_chunk data = data_queue.front();
        data_queue.pop();
        lk.unlock();
        process(data);
        if (is_last_chunk(data))
            break;
    }
}

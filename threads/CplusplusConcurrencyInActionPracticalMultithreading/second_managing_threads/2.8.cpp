/*
 * =====================================================================================
 *
 *       Filename:  2.8.cpp
 *
 *    Description:  a parallel version of std::accumulate
 *
 *        Version:  1.0
 *        Created:  2016年12月14日 21时22分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <chrono>

template <typename Iterator, typename T>
struct accumulate_block
{
    void operator()(Iterator first, Iterator last, T& result)
    {
        result = std::accumulate(first, last, result);
    }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    const unsigned long length = std::distance(first, last);

    if (!length)
        return init;

    const unsigned long min_per_thread = 25;
    const unsigned long max_threads = (length + min_per_thread - 1) / min_per_thread;
    const unsigned long hardware_threads = std::thread::hardware_concurrency();
    const unsigned long num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    const unsigned long block_size = length / num_threads;

    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1);
    
    Iterator block_start = first;
    for (unsigned long i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(
                accumulate_block<Iterator, T>(),
                block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    }
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return std::accumulate(results.begin(), results.end(), init);
};

int main(void)
{
    std::vector<int> ivec;
    for (int i = 0; i < 2000000; ++i) {
        ivec.push_back(1);
    }

    std::chrono::system_clock::time_point b = std::chrono::system_clock::now();
    std::cout << parallel_accumulate(ivec.begin(), ivec.end(), 0) << std::endl;
    std::chrono::system_clock::time_point e = std::chrono::system_clock::now();
    std::cout << (e - b).count() << std::endl;
    b = e;
    std::cout << std::accumulate(ivec.begin(), ivec.end(), 0) << std::endl;
    e = std::chrono::system_clock::now();
    std::cout << (e - b).count() << std::endl;
    return 0;
}

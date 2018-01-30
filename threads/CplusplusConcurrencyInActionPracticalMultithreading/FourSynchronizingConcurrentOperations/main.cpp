/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年12月17日 16时05分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include "thread_safe_queue.h"

int main(void)
{
    ThreadSafeQueue<int> tQueue;
    tQueue.push(10);
    std::cout << *tQueue.wait_and_pop() << std::endl;
    return 0;
}

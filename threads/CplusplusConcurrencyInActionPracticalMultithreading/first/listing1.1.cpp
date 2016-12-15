/*
 * =====================================================================================
 *
 *       Filename:  listing1.1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年12月14日 16时20分58秒
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

void hello()
{
    std::cout << "Hello Concurrent World!" << std::endl;
}

int main()
{
    std::thread t(hello);
    t.join();
    return 0;
}

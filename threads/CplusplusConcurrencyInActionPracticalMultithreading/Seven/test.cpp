/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年07月16日 23时20分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <memory>
#include <iostream>
#include <atomic>

int main(void)
{
    std::shared_ptr<int> a;
    std::cout << std::atomic_is_lock_free(&a) << std::endl;
    return 0;
}

/*
 * =====================================================================================
 *
 *       Filename:  spinlock.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年07月16日 14时51分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <atomic>

class spinlock_mutex {
private:
    std::atomic_flag flag;
public:
    spinlock_mutex():
        flag(ATOMIC_FLAG_INIT) {}

    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

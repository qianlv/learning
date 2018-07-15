/*
 * =====================================================================================
 *
 *       Filename:  enforcing_ordering_on_nonatomic_operations.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年07月15日 16时02分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <assert.h>

#include <iostream>
#include <atomic>
#include <thread>

bool x;
std::atomic<bool> y;
std::atomic<int> z;


void write_x_then_y() {
  x = true;
  std::atomic_thread_fence(std::memory_order_release);
  y.store(true, std::memory_order_relaxed);
}

void read_y_then_x() {
  while (!y.load(std::memory_order_relaxed)) {
  }
  std::atomic_thread_fence(std::memory_order_acquire);
  if (x)
    ++z;
}

int main(void) {
  x = false;
  y = false;
  z = 0;
  std::thread a(write_x_then_y);
  std::thread b(read_y_then_x);
  a.join();
  b.join();
  assert(z.load() != 0);
  return 0;
}

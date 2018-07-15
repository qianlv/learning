/*
 * =====================================================================================
 *
 *       Filename:  relaxed_operations_can_be_ordered_with_fences.cpp
 *
 *    Description:  Fence
 *
 *        Version:  1.0
 *        Created:  2018年07月15日 15时57分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>


std::atomic<bool> x, y;
std::atomic<int> z;


void write_x_then_y() {
  x.store(true, std::memory_order_relaxed);
  std::atomic_thread_fence(std::memory_order_release);
  y.store(true, std::memory_order_relaxed);
}

void read_y_then_x() {
  while (!y.load(std::memory_order_relaxed))
    ;
  std::atomic_thread_fence(std::memory_order_acquire);
  if (x.load(std::memory_order_relaxed))
    ++z;
}

int main(void)
{
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

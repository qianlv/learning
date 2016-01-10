/*
 * =====================================================================================
 *
 *       Filename:  allocater.cpp
 *
 *    Description:  Allocater
 *
 *        Version:  1.0
 *        Created:  2016年01月07日 14时23分05秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <memory>
using std::allocator;
using std::uninitialized_copy;
using std::uninitialized_fill_n;

int main()
{
    allocator<string> alloc;
    auto const p = alloc.allocate(10);
    auto q = p;
    alloc.construct(q++);
    alloc.construct(q++, 10, 'c');
    alloc.construct(q++, "hi");
    cout << *p << endl;
    cout << *(p + 1) << endl;
    while (q != p)
        alloc.destroy(--q);
    alloc.deallocate(p, 10);

    vector<int> ivec = {1, 2, 3, 4, 5, 6, 7};
    allocator<int> ialloc;
    auto ip = ialloc.allocate(ivec.size() * 2);
    auto iq = uninitialized_copy(ivec.begin(), ivec.end(), ip);
    uninitialized_fill_n(iq, ivec.size(), 42);
    for (size_t i = 0; i < ivec.size() * 2; ++i)
        cout << *(ip + i) << " ";
    cout << endl; 
}

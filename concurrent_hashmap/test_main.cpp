/*
 * =====================================================================================
 *
 *       Filename:  test_main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年12月04日 22时57分06秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
#include "concurrent_hashmap.h"

using namespace std;

int main()
{
    ConcurrentHashmap<int, int> hm;
    hm.insert(1, 10);
    hm.insert(2, 20);
    std::cout << hm.get(1).key_ << " | " << hm.get(1).val_ << std::endl;
}

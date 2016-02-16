/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2016年01月13日 14时00分15秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "hasptr.h"
#include <utility>

int main()
{
    HasPtr hp("one"), hp2("two"), hp3("three");
    hp = hp2;
    hp2 = std::move(hp3);
    hp.show();
    hp2.show();
}

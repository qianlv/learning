/*
 * =====================================================================================
 *
 *       Filename:  6_54.cpp
 *
 *    Description: 6.54 
 *
 *        Version:  1.0
 *        Created:  2015年12月13日 17时25分49秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

#include <vector>
using std::vector;

int print(int, int)
{
    return 0;
}

int main()
{
    typedef int (*pf)(int, int);
    vector<pf> pfvec = {print};

    using pf2 = int (*)(int, int);
    vector<pf2> pf2vec = {print};

    using pf3 = int (int, int);
    vector<pf3*> pf3vec = {print};

    using pf4 = decltype(print) *;
    vector<pf4> pf4vec = {print};

    typedef decltype(print) *pf5;
    vector<pf5> pf5vec = {print};


    return 0;
}

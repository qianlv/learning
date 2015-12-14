/*
 * =====================================================================================
 *
 *       Filename:  6_55.cpp
 *
 *    Description:  6.55
 *
 *        Version:  1.0
 *        Created:  2015年12月13日 17时32分16秒 CST
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

int print(int a, int b) { return 0; }
int add(int a, int b) { return a + b;}
int sub(int a, int b) { return a - b;}
int multi(int a, int b) { return a * b;}
int divide(int a, int b) { return b == 0 ? 0 : static_cast<int>(a / b);}

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

    pfvec.push_back(add);
    pfvec.push_back(sub);
    pfvec.push_back(multi);
    pfvec.push_back(divide);
    for (auto iter = pfvec.begin(); iter != pfvec.end(); ++iter)
        cout << (*iter)(1, 2) << endl;
    for (auto &f : pfvec)
        cout << (*f)(1, 2) << endl;


    return 0;
}

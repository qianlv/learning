/*
 * =====================================================================================
 *
 *       Filename:  other_iterator.cpp
 *
 *    Description:  Iterator
 *
 *        Version:  1.0
 *        Created:  2016年01月02日 20时35分59秒 CST
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

#include <list>
using std::list;

#include <algorithm>
#include <numeric>
#include <iterator>
using std::istream_iterator;
using std::ostream_iterator;

void print(list<int> lit)
{
    std::for_each(lit.begin(), lit.end(), [] (int a) { cout << a << " ";});
    cout << endl;
}

int main()
{
    list<int> lst = {1, 2, 3, 4};
    list<int> lst2, lst3, lst4;
    std::copy(lst.cbegin(), lst.cend(), std::front_inserter(lst2));
    std::copy(lst.cbegin(), lst.cend(), std::inserter(lst3, lst3.begin()));
    for (auto iter = lst.begin(); iter != lst.end(); ++iter)
        lst4.insert(lst4.begin(), *iter);
    print(lst2);
    print(lst3);
    print(lst4);
    istream_iterator<int> in(cin), eof;
    cout << std::accumulate(in, eof, 0) << endl;
    ostream_iterator<int> out_iter(cout, " ");
    for (auto e: lst)
        *out_iter++ = e;
    cout << endl;
    std::copy(lst.begin(), lst.end(), out_iter);
    cout << endl;
}

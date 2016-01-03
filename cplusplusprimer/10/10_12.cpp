/*
 * =====================================================================================
 *
 *       Filename:  10_12.cpp
 *
 *    Description:  10.12 
 *
 *        Version:  1.0
 *        Created:  2015年12月29日 16时31分01秒 CST
 *       Revision:  none
 *       Compiler:  g++
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

#include <algorithm>
#include <numeric>

#include "scales_data.h"

bool compare_isbn(const Scales_data &left, const Scales_data &right)
{
    return left.isbn() < right.isbn();
}

int main()
{
    vector<Scales_data> sdv = {Scales_data("abe"), Scales_data("cde")};
    sort(sdv.begin(), sdv.end(), compare_isbn);
    for (const auto &elem : sdv)
        print(cout, elem) << endl;
}

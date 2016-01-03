/*
 * =====================================================================================
 *
 *       Filename:  10_17.cpp
 *
 *    Description:  10.17
 *
 *        Version:  1.0
 *        Created:  2016年01月01日 16时45分56秒 CST
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

int main()
{
    vector<Scales_data> sdv = {Scales_data("abe"), Scales_data("cde")};
    sort(sdv.begin(), sdv.end(), 
         [] (const Scales_data &lh, const Scales_data &rh)
         {
            return lh.isbn() < rh.isbn();
         }
    );
    for (const auto &elem : sdv)
        print(cout, elem) << endl;
}

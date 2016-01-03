/*
 * =====================================================================================
 *
 *       Filename:  10_18_19.cpp
 *
 *    Description:  10.18 10.19
 *
 *        Version:  1.0
 *        Created:  2016年01月01日 16时48分39秒 CST
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

#include "generic_algorithm.h"

int main()
{
    vector<string> words = {"one", "two", "three", "four"};
    biggies_p(words, 4);

    vector<string> words2 = {"one", "two", "three", "four"};
    biggies_sp(words2, 4);
}

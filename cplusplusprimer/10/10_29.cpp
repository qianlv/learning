/*
 * =====================================================================================
 *
 *       Filename:  10_29.cpp
 *
 *    Description:  10.29
 *
 *        Version:  1.0
 *        Created:  2016年01月03日 13时09分43秒 CST
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

#include <fstream>
using std::ifstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>
#include <numeric>
#include <iterator>
using std::istream_iterator;
using std::ostream_iterator;

int main()
{
    ifstream infile("10_29.cpp");
    istream_iterator<string> ins(infile), eof;
    ostream_iterator<string> out(cout, "\n");
    vector<string> svec;
    std::copy(ins, eof, std::back_inserter(svec));
    std::copy(svec.begin(), svec.end(), out);
}

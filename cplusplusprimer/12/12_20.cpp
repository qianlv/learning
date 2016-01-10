/*
 * =====================================================================================
 *
 *       Filename:  10_20.cpp
 *
 *    Description:  10.20
 *
 *        Version:  1.0
 *        Created:  2016年01月06日 20时59分15秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>
#include <numeric>
#include <memory>
using std::make_shared;
using std::shared_ptr;

#include "blob.h"
#include "blobptr.h"

int main()
{
    ifstream infile("input.txt");
    string line;
    StrBlob str_blob;
    while (getline(infile, line))
    {
        str_blob.push_back(line);
    }
    for (auto iter = str_blob.begin(); iter != str_blob.end(); iter = iter.incr())
    {
        cout << iter.deref() << endl;
    }
}

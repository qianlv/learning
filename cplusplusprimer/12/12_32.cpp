/*
 * =====================================================================================
 *
 *       Filename:  12_32.cpp
 *
 *    Description:  12.32
 *
 *        Version:  1.0
 *        Created:  2016年01月07日 17时09分12秒 CST
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
#include <sstream>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ostream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <set>
using std::set;

#include "text_query_strblob.h"

void runQueries(ifstream &infile)
{
    TextQuery tq(infile);
    while (true)
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl;
    }
}

int main()
{
    ifstream infile("12_30.cpp");
    runQueries(infile);
}


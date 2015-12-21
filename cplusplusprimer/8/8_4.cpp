/*
 * =====================================================================================
 *
 *       Filename:  8_4.cpp
 *
 *    Description:  8.4
 *
 *        Version:  1.0
 *        Created:  2015年12月20日 17时52分58秒 CST
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
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    ifstream input(argv[1]);
    if (!input)
        return -1;

    string line;
    vector<string> svec;
    while (getline(input, line))
    {
        svec.push_back(line);
    }

    for (auto iter = svec.begin(); iter != svec.end(); ++iter)
        cout << *iter << endl;
}

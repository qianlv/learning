/*
 * =====================================================================================
 *
 *       Filename:  8_5.cpp
 *
 *    Description:  8.5
 *
 *        Version:  1.0
 *        Created:  2015年12月20日 19时07分24秒 CST
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

    string word;
    vector<string> svec;
    while (input >> word)
    {
        svec.push_back(word);
    }

    for (auto iter = svec.begin(); iter != svec.end(); ++iter)
        cout << *iter << endl;
}

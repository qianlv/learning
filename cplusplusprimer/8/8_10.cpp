/*
 * =====================================================================================
 *
 *       Filename:  8_10.cpp
 *
 *    Description:  8.10 
 *
 *        Version:  1.0
 *        Created:  2015年12月20日 19时36分21秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

ifstream& read_from_file(ifstream &file, vector<string> &vec)
{
    if (file)
    {
        string line;
        while (getline(file, line))
        {
            vec.push_back(line);
        }
    }
    return file;
}

void read_from_vec(const vector<string> &vec)
{
    string word;
    for(const auto &line : vec)
    {
        istringstream record(line);
        while (record >> word)
        {
            cout << word << endl; 
        }
    }
}

int main(int argc, char *argv[])
{
    ifstream file(argv[1]);
    vector<string> svec;
    read_from_file(file, svec);
    read_from_vec(svec);
}

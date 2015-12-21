/*
 * =====================================================================================
 *
 *       Filename:  stringio.cpp
 *
 *    Description:  String IO 
 *
 *        Version:  1.0
 *        Created:  2015年12月20日 19时26分56秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct PersonInfo {
    string name;
    vector<string> phones;
};

int main()
{
    string line, word;
    vector<PersonInfo> people;
    while (getline(cin, line))
    {
        PersonInfo info;
        istringstream record(line);
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }
}

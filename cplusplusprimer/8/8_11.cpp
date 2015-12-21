/*
 * =====================================================================================
 *
 *       Filename:  8_11.cpp
 *
 *    Description:  8.11
 *
 *        Version:  1.0
 *        Created:  2015年12月20日 19时47分10秒 CST
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
    istringstream record;
    while (getline(cin, line))
    {
        PersonInfo info;
        record.clear();
        record.str(line);
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }

    cout << people.size() << endl;
}


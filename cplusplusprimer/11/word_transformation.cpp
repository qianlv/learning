/*
 * =====================================================================================
 *
 *       Filename:  word_transformation.cpp
 *
 *    Description:  A Word Transformation
 *
 *        Version:  1.0
 *        Created:  2016年01月04日 21时58分00秒 CST
 *       Revision:  none
 *       Compiler:  gcc
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

#include <sstream>
using std::istringstream;

#include <fstream>
using std::ifstream;

#include <stdexcept>
using std::runtime_error;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <set>
using std::set;

#include <algorithm>
#include <numeric>

map<string, string> buildMap(ifstream &map_file)
{
    map<string, string> trans_map;
    string key, value;
    while (map_file >> key && getline(map_file, value))
    {
        if (value.size() > 1)
            trans_map[key] = value.substr(1);
        else
            throw runtime_error("no rule for " + key);
    }
    return trans_map;
}

const string &
transform(const string &s, const map<string, string> &m)
{
    map<string, string>::const_iterator map_it = m.find(s);
    if (map_it != m.end())
        return map_it->second;
    return s;
}
void word_transform(ifstream &map_file, ifstream &input)
{
    auto trans_map = buildMap(map_file);
    string text;
    while (getline(input, text))
    {
        istringstream stream(text);
        string word;
        bool first_word = true;
        while (stream >> word)
        {
            if (first_word)
                first_word = false;
            else
                cout << " ";
            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}
int main()
{
    ifstream map_file("rule.txt");
    ifstream input("text.txt");
    word_transform(map_file, input);
}

/*
 * =====================================================================================
 *
 *       Filename:  10_14.cpp
 *
 *    Description:  10.14
 *
 *        Version:  1.0
 *        Created:  2016年01月04日 14时43分30秒 CST
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

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <set>
using std::set;

#include <utility>
using std::pair;

#include <algorithm>
#include <numeric>

class Families
{
public:
    using Child    = pair<string, string>;
    using Children = vector<Child>;
    using Data     = map<string, Children>;

    void add(const string &last_name, const string &first_name, const string birthday)
    {
        auto child = std::make_pair(first_name, birthday);
        _data[last_name].push_back(child);
    }

    void print() const
    {
        for (const auto &p : _data)
        {
            cout << p.first << ":\n";
            for (const auto &child : p.second)
                cout << child.first << " " << child.second << endl;
            cout << endl;
        }
    }

private:
    Data _data;
};

int main()
{
    Families families;
    for (string l, f, b; cin >> l >> f >> b; families.add(l, f, b))
        ;
    families.print();
}

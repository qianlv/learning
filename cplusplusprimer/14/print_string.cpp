/*
 * =====================================================================================
 *
 *       Filename:  print_string.h
 *
 *    Description:  class Print String
 *
 *        Version:  1.0
 *        Created:  2016年02月19日 10时03分18秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::ostream;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class PrintString
{
public:
    PrintString(ostream &o = cout, char c = ' '):
        os(o), sep(c) {}
    void operator() (const string &s) const { os << s << sep; }
private:
    ostream& os;
    char sep;
};

int main()
{
    string s("Hello World!");
    PrintString printer;
    printer(s);
    PrintString errors(cerr, '\n');
    errors(s);
    errors(s);
    vector<string> sv{"one", "two", "three"};
    std::for_each(sv.begin(), sv.end(), errors);
}

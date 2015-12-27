/*
 * =====================================================================================
 *
 *       Filename:  9_51.cpp
 *
 *    Description:  9.51 
 *
 *        Version:  1.0
 *        Created:  2015年12月27日 19时00分24秒 CST
 *       Revision:  none
 *       Compiler:  g++
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
using std::stoi;

#include <cctype>
using std::tolower;

#include <vector>
using std::vector;

class Date
{
public:
    Date(unsigned int y, unsigned int m, unsigned int d):
        year(y), month(m), day(d) {}
    Date(string date)
    {
        string split(" ,/-");
        for (auto &elem : date)
            elem = tolower(elem);

        for (size_t i = 0; i < mstr.size(); ++i)
        {
            if (date.substr(0, mstr[i].size()) == mstr[i])
            {
                month = i + 1;
                break;
            }
            if (date.substr(0, mstr_abb[i].size()) == mstr_abb[i])
            {
                month = i + 1;
                break;
            }
        }

        string::size_type bpos = 0;
        string::size_type epos = 0;
        if (month == 0)
        {
            epos = date.find_first_of(split, 0);
            day = stoi(date.substr(bpos, epos - bpos));
        }

        bpos = date.find_first_of(split, 0) + 1;
        epos = date.find_first_of(split, bpos);
        day = stoi(date.substr(bpos, epos - bpos));

        ++epos; 
        year = stoi(date.substr(epos, date.size() - epos));
    }
    void print()
    {
        cout << year << " " << month << " " << day << endl;
    }
private:
    unsigned int year, month, day;
    static vector<string> mstr;
    static vector<string> mstr_abb;
};

vector<string> Date::mstr = {
    "january", "february", "march", "april",
    "may", "june", "july", "august", "september",
    "october", "november", "december" 
};

vector<string> Date::mstr_abb = {
    "jan", "feb", "mar", "apr", "may", "jun", "jul",
    "aug", "sept", "oct", "nov", "dec"
};

int main()
{
    Date date("apr/1-1900");
    date.print();
    Date date1("november-1,1900");
    date1.print();
}

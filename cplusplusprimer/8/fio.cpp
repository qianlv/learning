/*
 * =====================================================================================
 *
 *       Filename:  fio.cpp
 *
 *    Description:  file io
 *
 *        Version:  1.0
 *        Created:  2015年12月20日 17时23分35秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "scales_data.h"

void process(ifstream &is)
{
    string s;
    while (is >> s)
    {
        cout << s << endl;
    }
}

int main(int argc, char *argv[])
{

    for (char **p = argv + 1; p != argv + argc; ++p)
    {
        ifstream input(*p);
        if (input)
            process(input);
        else
            cerr << "couldn't open: " << string(*p) << endl;
    }
    ifstream input(argv[1]);
    ofstream output(argv[2]);

    Scales_data total;
    if (read(input, total))
    {
        Scales_data trans;
        while (read(input, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(output, total) << endl; 
                total = trans; 
            } 
        }
        print(output, total) << endl;
    }
    else
    {
        cerr << "No data?!" << endl;
    }
}

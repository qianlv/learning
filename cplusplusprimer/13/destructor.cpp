/*
 * =====================================================================================
 *
 *       Filename:  destructor.cpp
 *
 *    Description:  Destructor
 *
 *        Version:  1.0
 *        Created:  2016年01月10日 16时10分54秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cout;
using std::endl;
#include <memory>
using std::make_shared;

#include <vector>
using std::vector;

#include "scales_data.h"

int main()
{
    Scales_data *p = new Scales_data;
    cout << "-----" << endl;
    
    auto p2 = make_shared<Scales_data>();
    cout << "-----" << endl;

    Scales_data item(*p);
    cout << "-----" << endl;

    vector<Scales_data> vec;
    vec.push_back(*p2);
    cout << "-----" << endl;

    delete p;
}

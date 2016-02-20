/*
 * =====================================================================================
 *
 *       Filename:  emploee.h
 *
 *    Description:  Class Employee
 *
 *        Version:  1.0
 *        Created:  2016年01月11日 10时30分29秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef EMPLOEEE_H_
#define EMPLOEEE_H_

#include <iostream>
using std::istream;
using std::ostream;

#include <string>
using std::string;

class Employee
{
    friend istream& operator>> (istream &, Employee &);
    friend ostream& operator<< (ostream &, Employee &);
    friend bool operator== (const Employee &, const Employee &);
    friend bool operator!= (const Employee &, const Employee &);
public:
    Employee();
    Employee(const string &);
    Employee(const Employee&) = delete;
    Employee& operator= (const Employee&) = delete;
private:
    string name_;
    int id_;
    static int unique_id;
};

bool operator== (const Employee &, const Employee &);
bool operator!= (const Employee &, const Employee &);

#endif // EMPLOEEE_H_

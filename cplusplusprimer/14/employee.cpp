/*
 * =====================================================================================
 *
 *       Filename:  employee.cpp
 *
 *    Description:  employee
 *
 *        Version:  1.0
 *        Created:  2016年02月17日 10时57分29秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "employee.h"

int Employee::unique_id= 10000000;

Employee::Employee() : Employee("")
{
}

Employee::Employee(const string &name) : name_(name)
{
    id_ = unique_id++;
}

istream& operator>> (istream &is, Employee &employee)
{
    is >> employee.name_;
    return is;
}

ostream& operator<< (ostream &os, Employee &employee)
{
    os << employee.name_ << " " << employee.id_;
    return os;
}

bool operator== (const Employee &lep, const Employee &rep)
{
    return lep.id_ == rep.id_;
}

bool operator!= (const Employee &lep, const Employee &rep)
{
    return !(lep == rep);
}

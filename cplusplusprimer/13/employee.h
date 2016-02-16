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

#include <string>
using std::string;

class Employee
{
    Employee();
    Employee(const string &);
    Employee(const Employee&) = delete;
    Employee& operator= (const Employee&) = delete;
private:
    string name_;
    int id_;
    static int unique_id;
};

int Employee::unique_id= 10000000;

Employee::Employee() : Employee("")
{
}

Employee::Employee(const string &name) : name_(n)
{
    id_ = unique_id++;
}

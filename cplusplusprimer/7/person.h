/*
 * =====================================================================================
 *
 *       Filename:  person.h
 *
 *    Description:  Person
 *
 *        Version:  1.0
 *        Created:  2015年12月14日 19时21分53秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person
{
public:
    Person() = default;
    Person(const std::string &sname, const std::string &saddress) :
        name(sname), address(saddress) {}
    Person(std::istream &is) { read(is, *this); }
    auto get_name() const -> std::string const& { return name; }
    auto get_addr() const -> std::string const& { return address; }

private:
    std::string name;
    std::string address;
};

std::istream &read(std::istream &, Person &);
std::ostream &print(std::ostream &, const Person &);

#endif

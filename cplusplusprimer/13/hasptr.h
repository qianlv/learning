/*
 * =====================================================================================
 *
 *       Filename:  hasptr.h
 *
 *    Description:  Class HasPtr
 *
 *        Version:  1.0
 *        Created:  2016年01月10日 15时07分48秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef HASPTR_H_
#define HASPTR_H_

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

class HasPtr
{
public:
    friend void swap(HasPtr&, HasPtr&);

    HasPtr(const string &s = string());
    HasPtr(const HasPtr &hp);
    HasPtr(HasPtr &&) noexcept;
    ~HasPtr();

    // HasPtr& operator= (const HasPtr &rhs);
    HasPtr& operator= (HasPtr rhs);
    bool operator< (const HasPtr &rhs) const;

    void show();
    void swap(const HasPtr &);
    
private:
    string *ps;
    int     i;
};

void swap(HasPtr&, HasPtr&);

class HasPtrLikePointer
{
public:
    HasPtrLikePointer(const string &s = string());
    HasPtrLikePointer(const HasPtrLikePointer &);
    HasPtrLikePointer& operator= (const HasPtrLikePointer &);
    ~HasPtrLikePointer();
private:
    string *ps;
    int     i;
    size_t  *use;
};

#endif // HASPTR_H_

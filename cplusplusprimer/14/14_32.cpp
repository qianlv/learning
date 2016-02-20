/*
 * =====================================================================================
 *
 *       Filename:  14_32.cpp
 *
 *    Description:  14_32
 *
 *        Version:  1.0
 *        Created:  2016年02月18日 23时09分17秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "blobptr.h"
#include "blob.h"
#include "14_32.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

StrBlobPtr& StrBlobPtr_pointer::operator* () const
{
    return *pointer;
}

StrBlobPtr* StrBlobPtr_pointer::operator-> () const
{
    return & (this->operator*());
}

int main()
{
    StrBlob sv{"one", "two"};
    StrBlobPtr iter = sv.begin();
    StrBlobPtr_pointer p(&iter);
    cout << (*p).deref() << endl;
    cout << p->deref() << endl;

}

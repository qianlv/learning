/*
 * =====================================================================================
 *
 *       Filename:  14_32.h
 *
 *    Description:  14.32
 *
 *        Version:  1.0
 *        Created:  2016年02月18日 23时09分25秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

class StrBlobPtr;

class StrBlobPtr_pointer
{
public:
    StrBlobPtr_pointer() = default;
    StrBlobPtr_pointer(StrBlobPtr *p): pointer(p) {}
    StrBlobPtr& operator* () const;
    StrBlobPtr* operator-> () const;
private:
    StrBlobPtr *pointer = nullptr;
};

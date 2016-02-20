/*
 * =====================================================================================
 *
 *       Filename:  14_16.cpp
 *
 *    Description:  14.16
 *
 *        Version:  1.0
 *        Created:  2016年02月17日 17时56分05秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "blob.h"
#include "blobptr.h"
#include "str_vec.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    StrBlob sb({"a", "be"}), sb2({"ab", "be"});
    cout << (sb == sb2) << endl;

    StrVec svec = {"helo", "word", "one", "two"};
    StrVec svec2 = {"helo", "word", "one", "two"};
    cout << (svec == svec2) << endl;

    for (auto iter = sb.begin(); iter != sb.end(); iter = iter.incr())
    {
        cout << iter.deref() << endl;
    }
}

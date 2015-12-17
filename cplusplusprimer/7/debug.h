/*
 * =====================================================================================
 *
 *       Filename:  debug.h
 *
 *    Description:  Class Debug
 *
 *        Version:  1.0
 *        Created:  2015年12月17日 20时56分45秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

class Debug
{
public:
    constexpr Debug(bool b = true) : hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o) : 
        hw(h), io(i), other(o) {}
    constexpr bool any() { return hw || io || other; }
    void set_io(bool b) { io = b; }
    void set_hw(bool b) { hw = b; }
    void set_other(bool b) { other = b; }

private:
    bool hw;
    bool io;
    bool other;
};

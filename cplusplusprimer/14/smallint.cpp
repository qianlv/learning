/*
 * =====================================================================================
 *
 *       Filename:  smallint.cpp
 *
 *    Description:  class SmallInt, type change
 *
 *        Version:  1.0
 *        Created:  2016年02月20日 11时00分39秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <stdexcept>

class SmallInt
{
public:
    SmallInt(int i = 0): val(i) 
    {
        if (i < 0 || i > 256)
            throw std::out_of_range("Bad SmallInt value");
    }

    // explicit operator int() const { return val; }
    operator int() const { return val; }
private:
    std::size_t val;
};

int main()
{
    SmallInt si = 10;
    int v = static_cast<int>(si) + 4;
    v = si + 4;
    std::cout << v << std::endl;
}

/*
 * =====================================================================================
 *
 *       Filename:  multidim.cpp
 *
 *    Description:  多维数组
 *
 *        Version:  1.0
 *        Created:  2015年12月07日 21时20分37秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iterator>
using std::begin;
using std::end;

int main()
{
    // 初始化
    int ia[3][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11}
    };
    int ia1[3][4] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
    }; // 等价ia, 会有警告
    int ia2[3][4] = { { 0 }, { 4 }, { 8 } };

    // 多维下标引用
    int (&row)[4] = ia[1];
    for (int i = 0; i < 4; ++i)
        cout << row[i] << " ";
    cout << endl;

    constexpr size_t rowCnt = 3, colCnt = 4;
    int ia3[rowCnt][colCnt];
    for (size_t i = 0; i != rowCnt; ++i)
    {
        for (size_t j = 0; j != colCnt; ++j)
        {
            ia3[i][j] = i * colCnt + j;
        }
    }

    size_t cnt = 0;
    for (int (&row)[4] : ia3)
    {
        for (int &col : row)
        {
            col = cnt;
            ++cnt;
        }
    }

    cout << "----------" << endl;
    for (const auto &row : ia3)     // 此处使用引用目的是避免数组自动转换成指针
    {
        for (auto col : row)
        {
            // col = 10;
            cout << col << " ";
        }
        cout << endl;
    }

    // for (auto row : ia3)  // 此时row数组内首元素的指针, 类型 int* .
    // {
    //     for (auto col : row)
    //         cout << col << " ";
    //     cout << endl;
    // }

    cout << "----------" << endl;
    for (auto p = ia3; p != ia3 + 3; ++p)
    {
        for (auto q = *p; q != *p + 4; ++q)
            cout << *q << " ";
        cout << endl;
    }

    cout << "----------" << endl;
    for (auto p = begin(ia3); p != end(ia3); ++p)
    {
        for (auto q = begin(*p); q != end(*p); ++q)
            cout << *q << " ";
        cout << endl;
    }
}

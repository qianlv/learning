/*
 * =====================================================================================
 *
 *       Filename:  sort-colors-75.cpp
 *
 *    Description:  sort colors
 *
 *        Version:  1.0
 *        Created:  2016年06月02日 11时04分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

//#include <iostream>
//#include <algorithm>
//#include <vector>
//using namespace std;

//template <typename T>
//void output(const std::vector<T>& vec)
//{
    //std::for_each(vec.begin(), vec.end(),
                //[](const T& v) {
                    //cout << v << " ";
                //});
    //cout << endl;
//}

class Solution
{
public:
    void sortColors(vector<int>& nums)
    {
        int red = 0, white = 0, blue = 0;
        std::for_each(nums.begin(), nums.end(), [&] (int v) { 
                if (v == 0) ++red;
                else if (v == 1) ++white;
                else ++blue;
                });
        nums.clear();
        nums.insert(nums.end(), red, 0);
        nums.insert(nums.end(), white, 1);
        nums.insert(nums.end(), blue, 2);
    }
};

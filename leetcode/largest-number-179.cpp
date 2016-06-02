/*
 * =====================================================================================
 *
 *       Filename:  largest-number-179.cpp
 *
 *    Description:  largest number
 *
 *        Version:  1.0
 *        Created:  2016年06月02日 16时32分57秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7 at gmail dot com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

template <typename T>
void output(const std::vector<T>& vec)
{
    std::for_each(vec.begin(), vec.end(),
                [](const T& v) {
                    cout << v << " ";
                });
    cout << endl;
}

class Solution
{
public:
    static bool cmp(int l, int r)
    {
        int llen = lenVal(l);
        int rlen = lenVal(r);
        //cout << l << "-" << r << endl;
        //cout << llen << "+" << rlen << endl;
        int maxlen = std::max(llen, rlen);
        //cout << l <<"------" << r << endl;
        for (int i = 0; i < maxlen + 1; ++i)
        {
            int lv = getPosVal(l, i % llen);
            int rv = getPosVal(r, i % rlen);
            //cout << lv << "|" << rv << endl;
            if (lv > rv)
                return true;
            else if (lv < rv) 
            {
                return false;
            }
        }
        return false;
    }

    string largestNumber(vector<int>& nums)
    {
        if (std::count(nums.begin(), nums.end(), 0) == (long)nums.size())
            return "0";
        std::sort(nums.begin(), nums.end(), cmp);
        // output(nums);
        string res;
        for (auto val : nums)
            res += std::to_string(val);
        return res;
    }

    static int getPosVal(int v, int pos)
    {
        static const long base[] = {
            1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
        int len = lenVal(v);
        //cout << len << "|" << pos << endl;
        return v / base[len - pos - 1] % 10;
    }

    static int lenVal(int v)
    {
        if (v == 0)
            return 1;
        int i = 0;
        for (; v; ++i, v = v / 10)
            ;
        return i;
    }

};

int main()
{
    vector<int> vec = {3, 30, 34, 5, 9};
    vector<int> ivec = {
        7286,155,351,6059,9686,2668,9551,5410,
        7182,170,3746,3095,8139,2587,2351,2341,2038,
        3956,6034,4071,9473,281,9306,8746,7954,8937,
        7855,3938,9737,2455,4344,2986,8968,1072,2442,
        7191,9106,4236,2768,5214,7541,329,7530,9068,9644,
        3539,5177,5332,2065,8245,7494,8454,604,4632,1745,301
        ,3412,1569,8637,7840,7752,9536,1023,4841,1286,6489,8459,
        2725,8021,5026,7058,4540,9892,5344,1205,4363,959,9729,
        9225,9733,8417,9873,3721,1434,5136,6111,6189,780,4741,
        2670,2457,5424,1040,3746,1229,8568,3636,1546,2553,575};
    Solution sol;
    cout << sol.largestNumber(ivec) << endl;
}

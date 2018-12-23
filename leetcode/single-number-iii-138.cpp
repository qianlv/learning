#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int diff = std::accumulate(nums.begin(), nums.end(), 0, std::bit_xor<int>());
        diff &= -diff;
        vector<int> res(2, 0);
        for (int x : nums) {
            if (x & diff) {
                res[0] ^= x;
            } else {
                res[1] ^= x;
            }
        }
        return res;
    }
};

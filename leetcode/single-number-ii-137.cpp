#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> bits(32, 0);
        for (int x : nums) {
            for (int i = 0; i < 32; ++i) {
                if (x & (1 << i)) {
                    bits[i] += 1;
                }
            }
        }
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            bits[i] %= 3;
            if (bits[i] == 1) {
                res |= (1<<i);
            }
        }
        return res;
    }
};

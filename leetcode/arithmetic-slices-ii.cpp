#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        unordered_map<long long, set<int> > aMap;
        for (int i = 0; i < n; ++i) {
            aMap[A[i]].insert(i);
        }

        int ans = 0;
        for (int i = 2; i < n; ++i) {
            for (int j = 0; j < i; j++) {
                long long diff = 2 * (long long)A[j] - A[i];
                if (aMap.find(diff) != aMap.end()) {
                    for (int k : aMap[diff]) {
                        if (k < j) {
                            dp[i][j] += (1 + dp[j][k]);
                        }
                    }
                }
                ans += dp[i][j];
            }
        }
        return ans;
    }
};

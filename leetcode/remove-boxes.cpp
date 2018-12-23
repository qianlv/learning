#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int removeBoxes(const vector<int>& boxes) {
        int n = boxes.size();
        vector<vector<int> > dp(n, vector<int>(n+1, 0));
        for (int i = 0; i < n; ++i) {
            dp[i][1] = 1;
        }

        for (int k = 2; k <= n; ++k) {
            for (int i = k-1; i < n; ++i) {
                vector<std::pair<int, int> > rounds;
                bool first = true;
                int start = i - 1;
                int count = 0;
                // std::cout << "---: " << i << "-" << k << std::endl;
                for (int j = i-1; j >= i - (k - 1); j--) {
                    if (boxes[i] != boxes[j]) {
                        if (first) {
                            first = false;
                            start = j;
                        }
                        count += 1;
                    } else {
                        if (!first) {
                            rounds.push_back(std::make_pair(start, count));
                            // std::cout << start << "-" << count << std::endl;
                            first = true;
                            count = 0;
                        }
                    }
                }

                if (!first) {
                    rounds.push_back(std::make_pair(start, count));
                    // std::cout << start << "-" << count << std::endl;
                    first = true;
                    count = 0;
                }
                int val = 0;
                int same = k;
                for (auto& p : rounds) {
                    val += dp[p.first][p.second];
                    same -= p.second;
                }
                // std::cout << "same: " << same << std::endl;
                val += same * same;
                dp[i][k] = val;
            }
        }
        // for (int i = 0; i <= n; ++i) {
            // for (int j = 0; j < n; ++j) {
                // std::cout << dp[j][i] << " ";
            // }
            // std::cout << std::endl;
        // }
        return dp[n-1][n];
    }
};

int main(void)
{
    Solution sol = Solution();
    // int n = sol.removeBoxes({1, 3, 2, 2, 2, 3, 4, 3, 1});
    int n = sol.removeBoxes({10, 1, 1, 3, 10, 1, 3});
    std::cout << n << std::endl;
    return 0;
}

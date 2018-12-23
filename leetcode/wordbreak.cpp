#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.size() == 0) return false;

        vector<bool> dp(s.size()+1, false);
        dp[0] = true;
        // unordered_set<string> workSet(wordDict.begin(), wordDict.end());
        for (size_t i = 1; i <= s.size(); ++i) {
            for (auto word : wordDict) {
                if (i >= word.size()) {
                    if (word == s.substr(i - word.size(), word.size()) && dp[i - word.size()]) {
                        dp[i] = true;
                    }
                }
            }
        }
        return dp[s.size()];
    }
};

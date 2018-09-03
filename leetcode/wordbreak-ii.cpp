#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<vector<string> > ress(s.size() + 1);
        vector<bool> dp(s.size()+1, false);
        dp[0] = true;
        for (size_t i = 1; i <= s.size(); ++i) {
            for (size_t j = 0; j < wordDict.size(); ++j) {
                auto& word = wordDict[j];
                if (i >= word.size()) {
                    if (word == s.substr(i - word.size(), word.size()) && dp[i - word.size()]) {
                        dp[i] = true;
                        ress[i].push_back(word);
                    }
                }
            }
        }

        vector<string> res;
        if (!dp[s.size()]) {
            return res;
        }
        getResult("", s.size(), ress, res);
        return res;
    }

    void getResult(string str, int index, vector<vector<string> >& ress, vector<string>& res) {
        if (index == 0) {
            res.push_back(str);
        }

        for (auto& word : ress[index]) {
            if (str.empty()) {
                getResult(word, index - word.size(), ress, res);
            } else {
                getResult(word + " " + str, index - word.size(), ress, res);
            }
        }
    }
};


int main(void)
{
    return 0;
}

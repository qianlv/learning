#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
private:
    constexpr static int TRIE_SIZE = 26;
    struct node {
        bool isEnd;
        struct node* next[TRIE_SIZE];
        node(): isEnd(false) {
            for (int i = 0; i < TRIE_SIZE; ++i) {
                next[i] = nullptr;
            }
        }
    };
    node trieRoot;

public:
    vector<string> findAllConcatenatedWordsInADict(const vector<string>& words) {
        unordered_set<string> wordSet(words.begin(), words.end());
        vector<string> res;
        for (auto& word : words) {
            if (dfs(wordSet, word, 0) > 1) {
                res.push_back(word);
            }
        }
        return res;
    }

    int dfs(const unordered_set<string>& wordSet,
            const string& word, size_t idx) {
        if (idx == word.size()) return 0;

        for (size_t i = idx; i < word.size(); ++i) {
            if (wordSet.find(word.substr(idx, i - idx + 1)) == wordSet.end()) {
                continue;
            }
            int count = dfs(wordSet, word, i + 1);
            if (count != -1) {
                return count + 1;
            }
        }
        return -1;
    }

    vector<string> findAllConcatenatedWordsInADict1(const vector<string>& words) {
        for (const auto& word : words) {
            addWord(word);
        }

        vector<string> res;
        for (const auto& word : words) {
            // std::cout << word << std::endl;
            if (countConcatenatedWords(&trieRoot, 0, 0, word)) {
                res.push_back(word);
            }
        }
        return res;
    }

    bool countConcatenatedWords(node* root, int index, int count, const string& word) {
        node* cur = root;
        int n = word.size();
        // std::cout << "index:" << index << std::endl;
        for (int i = index; i < n; ++i) {
            if (!cur->next[word[i] - 'a']) {
                return false;
            }
            cur = cur->next[word[i] - 'a'];
            if (cur->isEnd) {
                // std::cout << word[i] << std::endl;
                // std::cout << count << std::endl;
                if (i == n - 1) {
                    return count >= 1;
                } 
                if (countConcatenatedWords(root, i + 1, count + 1, word)) {
                    return true;
                }
            }
        }
        return false;
    }

    void addWord(const string& word) {
        node* root = &trieRoot;
        for (auto& c : word) {
            if (!root->next[c - 'a']) {
                root->next[c - 'a'] = new node;
            }
            root = root->next[c - 'a'];
        }
        root->isEnd = true;
    }
};

int main(void)
{
    Solution sol = Solution();
    vector<string> res = sol.findAllConcatenatedWordsInADict(
        {"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"});
    for (auto r : res) {
        std::cout << r << std::endl;
    }
    return 0;
}

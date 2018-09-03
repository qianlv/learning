#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(const vector<int>& nums) {
        vector<vector<int> > allRes;
        vector<int> res;
        solve(0, nums, allRes, res);
        return allRes;
    }

    void solve(int index, const vector<int>& nums,
            vector<vector<int> >& allRes, vector<int>& res) {
        if (index == static_cast<int>(nums.size())) {
            allRes.push_back(res);
            return;
        }
        res.push_back(nums[index]);
        solve(index + 1, nums, allRes, res);
        res.pop_back();
        solve(index + 1, nums, allRes, res);
    }
};

int main(void)
{
    Solution sol;
    sol.subsets({1, 2, 3});
    return 0;
}

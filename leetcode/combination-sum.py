""" 递归求解
"""


class Solution:
    # @param {integer[]} candidates
    # @param {integer} target
    # @return {integer[][]}
    def combinationSum(self, candidates, target):
        candidates.sort()
        curres = []
        result = []
        import copy

        def dfs(deep, target):
            if target == 0:
                result.append(copy.copy(curres))
            if deep >= len(candidates):
                return
            n = target / candidates[deep]
            if n == 0:
                return
            for i in range(n + 1):
                for j in range(i):
                    curres.append(candidates[deep])
                dfs(deep+1, target - i * candidates[deep])
                for j in range(i):
                    curres.pop()
        dfs(0, target)
        return result

if __name__ == '__main__':
    sol = Solution()
    print sol.combinationSum([2, 2], 4)

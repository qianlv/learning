
class Solution:
    # @param {integer[]} candidates
    # @param {integer} target
    # @return {integer[][]}
    def combinationSum2(self, candidates, target):
        candidates.sort()
        nlen = len(candidates)
        num = [1] * nlen
        j = 0
        for i in range(1, nlen):
            if candidates[i] == candidates[j]:
                num[j] += 1
            else:
                j += 1
                candidates[j] = candidates[i]
        del candidates[j+1:]
        del num[j+1:]
        # print num
        # print candidates

        curres = []
        result = []
        import copy

        def dfs(deep, target):
            # print deep, target
            if target == 0:
                # print curres
                result.append(copy.copy(curres))
                return
            if target < 0 or deep >= len(candidates):
                return

            for i in range(num[deep]+1):
                if target - candidates[deep] * i < 0:
                    break
                for j in range(i):
                    curres.append(candidates[deep])
                dfs(deep+1, target - candidates[deep] * i)
                for j in range(i):
                    curres.pop()
        dfs(0, target)
        return result
if __name__ == '__main__':
    sol = Solution()
    sol.combinationSum2([10, 1, 2, 7, 6, 1, 5], 8)

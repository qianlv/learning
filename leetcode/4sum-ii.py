from collections import defaultdict

class Solution:
    def fourSumCount(self, A, B, C, D):
        """
        :type A: List[int]
        :type B: List[int]
        :type C: List[int]
        :type D: List[int]
        :rtype: int
        """
        res1 = defaultdict(int)
        for x in A:
            for y in B:
                res1[x + y] += 1
        res2 = defaultdict(int)
        for x in C:
            for y in D:
                res2[x + y] += 1
        res = 0
        for k in res1:
            res += res2[-k] * res1[k]
        return res


if __name__ == "__main__":
    sol = Solution()
    print(sol.fourSumCount([-1, -1], [-1, 1], [-1, 1], [-1, 1]))
    #  print(sol.fourSumCount([1, 2], [-2, -1], [-1, 2], [0, 2]))
    #  print(sol.fourSumCount([1, 1], [1, 2], [1, 3], [1, 2]))

class Solution:
    # @param {string} s
    # @return {integer}
    def lengthOfLongestSubstring(self, s):
        res = 0
        cur = -1
        distances = [-1] * 256
        for i, v in enumerate(s):
            cur = max(cur, distances[ord(v)])
            res = max(res, i - cur)
            distances[ord(v)] = i
        print res
        return res

if __name__ == '__main__':
    sol = Solution()
    sol.lengthOfLongestSubstring('ab')

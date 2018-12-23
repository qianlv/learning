# encoding=utf-8
# trick: ans > (2 ^ 31 - 1) return 0


class Solution:
    # @param {integer} x
    # @return {integer}
    def reverse(self, x):
        ans = 0
        tmpx = -x if x < 0 else x
        while tmpx:
            ans = ans * 10 + tmpx % 10
            tmpx /= 10
        # print -ans if x < 0 else ans
        if ans > (2 ** 31 - 1):
            return 0
        return -ans if x < 0 else ans

if __name__ == '__main__':
    sol = Solution()
    sol.reverse(-123)

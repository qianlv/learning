# encoding=utf-8


class Solution:
    # @param {string} str
    # @return {integer}
    def myAtoi(self, str):
        str = str.strip()
        if len(str) <= 0:
            return 0
        sign = -1 if str[0] == '-' else 1

        if str[0] == '-' or str[0] == '+':
            str = str[1:]
        if len(str) <= 0:
            return 0

        ans = 0
        for s in str:
            if self.isdigital(s):
                ans = ans * 10 + int(s)
            else:
                break
        ans = sign * ans
        if ans > (2 ** 31 - 1):
            return 2 ** 31 - 1
        if ans < -2 ** 31:
            return -2 ** 31
        return ans

    def isdigital(self, s):
        try:
            int(s)
        except ValueError:
            return False
        return True

if __name__ == '__main__':
    sol = Solution()
    print sol.myAtoi("-2147483648")

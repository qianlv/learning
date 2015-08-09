# encoding=utf-8


class Solution:
    # @param {integer} x
    # @return {boolean}
    def isPalindrome(self, x):
        # 转化为字符串(感觉不可以?)
        # return str(x) == ''.join(list(reversed(str(x))))
        # 或 return str(x) == str(x)[::-1]
        ans = 0
        if x < 0:
            return False

        # 翻转数x
        tmpx = x
        while tmpx:
            ans = ans * 10 + (tmpx % 10)
            tmpx /= 10
        print ans
        return ans == x

if __name__ == '__main__':
    sol = Solution()
    print sol.isPalindrome(1)

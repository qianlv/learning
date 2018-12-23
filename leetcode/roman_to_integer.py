# I=1, V=5, X=10, L=50, C=100, D=500, M=1000


class Solution(object):
    ROMAN = [
        "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
    ]
    ROMANINT = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]

    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """
        num = 0
        for i, v in enumerate(self.ROMAN):
            while s.startswith(v):
                num += self.ROMANINT[i]
                s = s[len(v):]
        return num


if __name__ == '__main__':
    sol = Solution()
    print sol.romanToInt('MMMCMXCIX')

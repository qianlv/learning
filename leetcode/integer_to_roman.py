# I=1, V=5, X=10, L=50, C=100, D=500, M=1000


class Solution(object):
    ROMAN = [
        "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
    ]
    ROMANINT = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]

    def intToRoman(self, num):
        """
        :type num: int
        :rtype: str
        """
        res = ''
        for i, v in enumerate(self.ROMANINT):
            res += num / v * self.ROMAN[i]
            num %= v
        return res


if __name__ == '__main__':
    sol = Solution()
    print sol.intToRoman(3999)

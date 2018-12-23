# encoding=utf-8

from itertools import product


class Solution(object):
    def letterCombinations(self, digits):
        """
        :type digits: str
        :rtype: List[str]
        """
        letters = [
            '',
            '', 'abc', 'def',
            'ghi', 'jkl', 'mno',
            'pqrs', 'tuv', 'wxyz',
        ]
        args = [letters[int(x)] for x in digits]
        if args:
            return [''.join(x) for x in product(*args)]
        else:
            return []

if __name__ == '__main__':
    sol = Solution()
    print sol.letterCombinations('')

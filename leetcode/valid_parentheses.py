# encoding=utf-8


class Solution(object):
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        left_parenthese = '([{'
        right_parenthese = ')]}'
        right_left = dict(zip(right_parenthese, left_parenthese))
        # print right_left
        stack = []
        for p in s:
            if p in left_parenthese:
                stack.append(p)
            else:
                if stack and right_left[p] == stack[-1]:
                    stack.pop()
                    continue
                return False
        return len(stack) == 0

if __name__ == '__main__':
    sol = Solution()
    print sol.isValid('')

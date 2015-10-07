# encoding=utf-8


class Solution(object):
    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """
        stack = []
        ans = [0 for i in xrange(len(s) + 1)]
        max_ans = 0
        for i, p in enumerate(s):
            if p == '(':
                stack.append(i)
            else:
                if len(stack) > 0:
                    j = stack.pop()
                    # print 'j = ', j
                    ans[i] = ans[i - 1] + ans[j - 1] + 2
                    max_ans = max(ans[i], max_ans)
        return max_ans

if __name__ == '__main__':
    sol = Solution()
    print sol.longestValidParentheses("(()())")
    print sol.longestValidParentheses("(()()")

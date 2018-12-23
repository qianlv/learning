# encoding=utf-8


class Solution(object):
    def generateParenthesis(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        self.res = []
        self.dfs(n, n, '')
        return self.res

    def dfs(self, left, right, s):
        if left == 0 and right == 0:
            self.res.append(s)
            return
        if left > 0:
            self.dfs(left - 1, right, s + '(')
        if right > 0 and right - 1 >= left:
            self.dfs(left, right - 1, s + ')')

if __name__ == '__main__':
    sol = Solution()
    # print sol.generateParenthesis(1)
    # print sol.generateParenthesis(2)
    res = sol.generateParenthesis(4)
    print res
    res.append(-1)
    # t = ["(((())))","((()()))","((())())","((()))()","(()(()))","(()()())",
    # "(()())()","(())(())","(())()()","()((()))","()(()())","()(())()",
    # "()()(())","()()()()"]
    # for x in t:
    #     if x not in res:
    #         print x

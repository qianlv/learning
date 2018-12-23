# encoding=utf-8


class Solution:
    # @param {string} s
    # @param {string} p
    # @return {boolean}
    def isMatch(self, s, p):
        listp = self.formatReS(p)
        if not self.check(s, listp):
            return False
        p = ''.join(listp)
        # print p
        return self.match(s, p)

    def match(self, s, p):
        i = 0
        j = 0
        # 加入结束符, 简化处理
        s += '$'
        p += '$'
        m = len(s)
        n = len(p)
        # print m, n
        while j < n and i < m:
            if j + 1 < n and p[j + 1] == '*':
                if p[j] == '.':
                    for k in range(m + 1 - i):
                        if (self.match(s[i + k:], p[j + 2:])):
                            return True
                else:
                    for k in range(m + 1 - i):
                        # print "(", i, k, len(s)
                        if k == 0:
                            if (self.match(s[i + k:], p[j + 2:])):
                                return True
                        elif s[i + k - 1] == p[j]:
                            if (self.match(s[i + k:], p[j + 2:])):
                                return True
                        else:
                            return False
                return False

            if p[j] != '.' and p[j] != s[i]:
                return False
            i += 1
            j += 1

        if i == m and j == n:
            return True
        return False

    def formatReS(self, s):
        n = len(s)
        lists = []
        i = 0
        while i < n:
            if i + 1 < n and s[i] != '*' and s[i + 1] == '*':
                if len(lists) < 1 or s[i:i + 2] != lists[-1]:
                    lists.append(s[i:i + 2])
                i += 2
            else:
                lists.append(s[i:i + 1])
                i += 1
        return lists

    def check(self, s, listp):
        s = set(s)
        for item in listp:
            if len(item) == 1 and item != '.' and item not in s:
                return False
        return True

if __name__ == '__main__':
    sol = Solution()
    print sol.isMatch('aa', 'a')
    print sol.isMatch('aa', 'aa')
    print sol.isMatch('aaa', 'aa')
    print sol.isMatch('aa', 'a*')
    print sol.isMatch('aa', '.*')
    print sol.isMatch('ab', '.*')
    print sol.isMatch('aab', 'c*a*b')
    print sol.isMatch("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c")
    print sol.isMatch("bbbacbcbcbbbbabbbab", "b*c*c*.*.*.*ab*c")
    print sol.isMatch("aaa", "a.a")
    print sol.isMatch("a", "ab*")

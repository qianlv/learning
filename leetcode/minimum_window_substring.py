# encoding=utf-8

from collections import defaultdict


class Solution(object):
    def minWindow(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """
        tdict = defaultdict(int)
        tset = set(t)
        for v in t:
            tdict[v] += 1

        b, e = 0, 0
        judge = len(tset)
        if judge == 0:
            return ""
        minlen = len(s) + 1
        minb = None
        while e < len(s):
            if s[e] in tset:
                judge -= (tdict[s[e]] == 1)
                tdict[s[e]] -= 1

            while judge == 0 and b <= e:
                if judge == 0:
                    if minlen > e - b + 1:
                        minlen = e - b + 1
                        minb = b
                if s[b] in tset:
                    judge += (tdict[s[b]] == 0)
                    tdict[s[b]] += 1
                b += 1
            e += 1

        if minb is None:
            return ""
        return s[minb:minb + minlen]

if __name__ == '__main__':
    sol = Solution()
    print sol.minWindow("cacae", "ae")
    print sol.minWindow("cabwefgewcwaefgcf", "cae")

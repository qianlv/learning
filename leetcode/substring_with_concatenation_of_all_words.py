# encoding=utf-8

from collections import defaultdict


class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        vis = defaultdict(int)
        for word in words:
            vis[word] += 1
        wlen = len(words[0])
        wslen = wlen * len(words)
        i = 0
        res = []
        while i < len(s) - wslen + 1:
            b = i
            e = i + wslen
            use = defaultdict(int)
            while i < e:
                tmpw = s[i:i + wlen]
                if tmpw not in vis:
                    break
                use[tmpw] += 1
                if use[tmpw] > vis[tmpw]:
                    break
                i += wlen
            if i == e:
                res.append(b)
            i = b + 1
        return res

if __name__ == '__main__':
    sol = Solution()
    # print sol.findSubstring('aaaabbaaa', ['a'])
    print sol.findSubstring("barfoothefoobarman", ["foo", "bar"])

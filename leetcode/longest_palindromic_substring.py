class Solution:
    # @param {string} s
    # @return {string}
    def longestPalindrome(self, s):
        n = len(s)
        self.mod = 2 ** 31 - 1
        self.initMod(n)
        self.hval1 = self.initHashString(s)
        self.hval2 = self.initHashString(reversed(s))
        ans_p = 0
        ans_l = 0
        for i in range(n):
            l = 0
            r = min(i, n - 1 - i)
            while l <= r:
                mid = l + (r - l) / 2
                res = self.isPalindromic(i - mid, i + mid, n)
                if res:
                    l = mid + 1
                else:
                    r = mid - 1

            print i, r * 2 + 1
            if ans_l < r * 2 + 1:
                ans_l = r * 2 + 1
                ans_p = i - r
            l = 1
            r = min(i, n - i)
            while l <= r:
                mid = l + (r - l) / 2
                res = self.isPalindromic(i - mid, i + mid - 1, n)
                if res:
                    l = mid + 1
                else:
                    r = mid - 1

            print i, r * 2
            if ans_l < r * 2:
                ans_l = r * 2
                ans_p = i - r

        print ans_p, ans_l
        print s[ans_p: ans_p + ans_l]
        return s[ans_p: ans_p + ans_l]

    def initHashString(self, s):
        hval = [0]
        for i, c in enumerate(s):
            hval.append((hval[i] * 131 + ord(c)) % self.mod)
        return hval

    def initMod(self, n):
        self.powval = [1]
        for i in range(n):
            self.powval.append((self.powval[i] * 131) % self.mod)

    def getHashString(self, hval, i, j):
        i += 1
        j += 1
        return ((hval[j] - hval[i-1] * (self.powval[j - i + 1]))
                % self.mod + self.mod) % self.mod

    def isPalindromic(self, i, j, n):
        h1 = self.getHashString(self.hval1, i, j)
        h2 = self.getHashString(self.hval2, n - 1 - j, n - 1 - i)
        return h1 == h2

if __name__ == '__main__':
    sol = Solution()
    sol.longestPalindrome('abacfababa')

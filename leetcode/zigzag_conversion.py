# encoding=utf-8
# simple problem


class Solution:
    # @param {string} s
    # @param {integer} numRows
    # @return {string}
    def convert(self, s, numRows):
        if numRows <= 1:
            return s
        dis = (numRows - 1) * 2
        n = len(s)
        convert_s = [0] * n
        convert_len = 0
        for i in range(min(n, numRows)):
            if i == 0 or i == numRows - 1:
                j = 0
                while i + dis * j < n:
                    convert_s[convert_len] = s[i + dis * j]
                    convert_len += 1
                    j += 1
            else:
                dis1 = dis - i * 2
                dis2 = dis - dis1
                convert_s[convert_len] = s[i]
                convert_len += 1
                cur = i
                while True:
                    cur += dis1
                    if cur >= n:
                        break
                    convert_s[convert_len] = s[cur]
                    convert_len += 1

                    cur += dis2
                    if cur >= n:
                        break
                    convert_s[convert_len] = s[cur]
                    convert_len += 1
        # print convert_s
        return ''.join(convert_s)

if __name__ == '__main__':
    sol = Solution()
    print sol.convert("P", 3)

# encoding=utf-8
# 等价于求第k小
# 二分k，nums1 取前mid个值，那么nums2则取前k-mid个值，
# 如果nums2[k - mid -2] <=  [nums1[mid -1 ] <= nums2[k - mid - 1]
# 则符合条件


class Solution:
    # @param {integer[]} nums1
    # @param {integer[]} nums2
    # @return {float}
    def findMedianSortedArrays(self, nums1, nums2):
        m = len(nums1)
        n = len(nums2)
        if (m + n) % 2 == 0:
            k1 = (m + n) / 2
            k2 = k1 + 1
            v1 = self.findKSortedArrays(nums1, nums2, k1)
            if v1 == -1:
                v1 = self.findKSortedArrays(nums2, nums1, k1)
            print k1, v1
            v2 = self.findKSortedArrays(nums1, nums2, k2)
            if v2 == -1:
                v2 = self.findKSortedArrays(nums2, nums1, k2)
            print k2, v2
            return (v1 + v2) / 2.0
        else:
            k1 = (m + n) / 2 + 1
            v1 = self.findKSortedArrays(nums1, nums2, k1)
            if v1 == -1:
                v1 = self.findKSortedArrays(nums2, nums1, k1)
            print k1, v1
            return v1 + 0.0

    def findKSortedArrays(self, nums1, nums2, k):
        m = len(nums1)
        n = len(nums2)
        if n == 0:
            if k <= m:
                return nums1[k - 1]
            else:
                return -1
        r = min(m - 1, k - 1)
        l = 0
        while l <= r:
            mid = l + (r - l) / 2
            mval = nums1[mid]
            i = k - mid - 2
            lval = nums2[i] if i != -1 and i < n else i
            rval = nums2[i+1] if i+1 < n else -1
            res = self.check(mval, lval, rval)
            if i >= n:
                res = 1
            if res == 0:
                return mval
            elif res < 0:
                r = mid - 1
            else:
                l = mid + 1
        return -1

    def check(self, mval, lval, rval):
        if lval == -1:
            if rval >= mval:
                return 0
            else:
                return -1
        elif rval == -1:
            if lval <= mval:
                return 0
            else:
                return 1
        else:
            if lval <= mval <= rval:
                    return 0
            elif lval <= mval and rval <= mval:
                return -1
            else:
                return 1

if __name__ == '__main__':
    sol = Solution()
    print sol.findMedianSortedArrays([1], [2, 3, 4, 5, 6])

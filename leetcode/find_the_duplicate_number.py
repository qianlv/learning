# encoding=utf-8


class Solution(object):
    def findDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        low = 1
        high = len(nums) - 1
        while low <= high:
            mid = low + (high - low) / 2
            lte_sum = sum(x <= mid for x in nums)
            if lte_sum > mid:
                high = mid - 1
            else:
                low = mid + 1
        return low

if __name__ == '__main__':
    sol = Solution()
    print sol.findDuplicate([1, 1])

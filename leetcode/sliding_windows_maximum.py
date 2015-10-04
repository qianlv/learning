# encoding=utf-8
''' 单调队列, 此题维护单调递减队列
'''


class Solution(object):
    def maxSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        queue = []
        maxs = []
        if not nums or k <= 0:
            return maxs

        for i, num in enumerate(nums):
            while len(queue) != 0 and nums[queue[-1]] <= num:
                del queue[-1]
            queue.append(i)
            while i - queue[0] + 1 > k:
                del queue[0]
            if i >= k - 1:
                maxs.append(nums[queue[0]])
        return maxs

    def maxSlidingWindow_rmq(self, nums, k):
        pass

if __name__ == '__main__':
    sol = Solution()
    print sol.maxSlidingWindow([1, 3, -1, -3, 5, 3, 6, 7], 3)
    print sol.maxSlidingWindow([1], 1)

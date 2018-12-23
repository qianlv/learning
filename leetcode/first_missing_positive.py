# encoding=utf-8
# 鸽笼原理, 最小缺失的整数必定在[1, len(nums) + 1]之间


class Solution(object):
    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # return self.firstMissingPositive1(nums)
        return self.firstMissingPositive2(nums)

    def firstMissingPositive2(self, nums):
        nnums = len(nums)
        for i in xrange(nnums):
            while nums[i] > 0 and nums[i] <= nnums and \
                    nums[i] != nums[nums[i] - 1]:
                tmp = nums[i] - 1
                nums[i], nums[tmp] = nums[tmp], nums[i]

        for i in xrange(nnums):
            if nums[i] != i + 1:
                return i + 1
        return nnums + 1

    def firstMissingPositive1(self, nums):
        vis = {}
        nnums = len(nums) + 1
        for num in nums:
            if num < 0 or num > nnums:
                continue
            vis[num] = True
        for i in xrange(1, nnums + 1):
            if i not in vis:
                return i

if __name__ == '__main__':
    sol = Solution()
    print sol.firstMissingPositive([1])
    print sol.firstMissingPositive([3, 3, 4, -1, 1, 10])

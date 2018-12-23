# encoding=utf-8


class Solution(object):
    def threeSumClosest(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        nums.sort()
        n = len(nums)
        ans = None
        for i in range(n - 2):
            j, k = i + 1, n - 1
            while j < k:
                result = nums[i] + nums[j] + nums[k]
                if result == target:
                    return target
                ans = result if ans is None else ans
                if abs(result - target) < abs(ans - target):
                    ans = result
                if result > target:
                    k -= 1
                else:
                    j += 1
        return ans

if __name__ == '__main__':
    sol = Solution()
    print sol.threeSumClosest([-1, 2, 1, -4], -4)

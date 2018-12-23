# encoding=utf-8


class Solution(object):
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        return self.threeSum_fast(nums)
        # def check(nums, val, low, high):
        #     while low <= high:
        #         mid = (low + high) >> 1
        #         if nums[mid] == val:
        #             return True
        #         elif nums[mid] > val:
        #             high = mid - 1
        #         else:
        #             low = mid + 1
        #     return False

        # nums.sort()
        # res = []
        # n = len(nums)
        # for i, x in enumerate(nums):
        #     for j, y in enumerate(nums[i+1:]):
        #         val = -(x + y)
        #         if val < y:
        #             continue
        #         if not check(nums, val, i + j + 2, n - 1):
        #             continue
        #         res.append((x, y, val))

        # return list(set(res))

    def threeSum_fast(self, nums):
        nums.sort()
        # print nums
        res = []
        n = len(nums)
        for i in xrange(0, n - 2):
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            j = i + 1
            k = n - 1
            # print i, j
            while j < k:
                # print j, k
                val = nums[i] + nums[j] + nums[k]
                if val == 0:
                    res.append((nums[i], nums[j], nums[k]))
                    while j < k and nums[j] == nums[j + 1]:
                        j += 1
                    j += 1
                    while k > j and nums[k] == nums[k - 1]:
                        k -= 1
                    k -= 1
                elif val < 0:
                    while j < k and nums[j] == nums[j + 1]:
                        j += 1
                    j += 1
                else:
                    while k > j and nums[k] == nums[k - 1]:
                        k -= 1
                    k -= 1

        return res


if __name__ == '__main__':
    sol = Solution()
    print sol.threeSum([-2, 0, 1, 1, 2])

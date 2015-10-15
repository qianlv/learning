# encoding=utf-8

from collections import defaultdict


class Solution(object):
    def fourSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        nums.sort()
        # print nums
        hash_map = defaultdict(list)
        res = []
        n = len(nums)
        for i in xrange(n):
            for j in xrange(i + 1, n):
                tmp = nums[i] + nums[j]
                value = target - tmp
                tmp_list = hash_map[value]
                nl = len(tmp_list)
                for k in xrange(nl):
                    item = tmp_list[k]
                    if i > max(item) and j > max(item):
                        # print item, i, j, tmp_list, k
                        if k - 1 >= 0:
                            pre_item = tmp_list[k - 1]
                            # print pre_item
                            if nums[item[0]] == nums[pre_item[0]] and \
                               nums[item[1]] == nums[pre_item[1]]:
                                continue
                        ans = [nums[item[0]], nums[item[1]], nums[i], nums[j]]
                        res.append(tuple(ans))

                hash_map[tmp].append((i, j))
        return list(set(res))

if __name__ == '__main__':
    sol = Solution()
    # print sol.fourSum([-3,-2,-1,0,0,1,2,3], 0)
    # print sol.fourSum([0, 0, 0, 0], 0)
    # [[-2,-1,0,3],[-1,0,0,1],[-2,0,0,2],[-3,0,0,3],[-2,-1,0,3],[-3,0,1,2],[-2,-1,1,2],[-3,-1,1,3],[-3,-2,2,3]]
    # [[-3,-2,2,3],[-3,-1,1,3],[-3,0,0,3],[-3,0,1,2],[-2,-1,0,3],[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

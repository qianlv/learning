# encoding=utf-8
# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None

from heapq import heappush
from heapq import heappop


class Solution(object):
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        res = ListNode(-1)
        tmp = res
        priority_queue = []
        for i, node in enumerate(lists):
            if node is None:
                continue
            heappush(priority_queue, (node.val, i))
            lists[i] = node.next

        while True:
            try:
                val, i = heappop(priority_queue)
            except IndexError:
                break

            tmp.next = ListNode(val)
            tmp = tmp.next

            node = lists[i]
            if node is not None:
                heappush(priority_queue, (node.val, i))
                lists[i] = node.next

        return res.next
    # 为优化递归方式超时
    # def mergeKLists(self, lists):
    #     """
    #     :type lists: List[ListNode]
    #     :rtype: ListNode
    #     """
    #     maxnode = None
    #     maxi = -1
    #     for i, node in enumerate(lists):
    #         if node is None:
    #             continue
    #         if maxnode is None:
    #             maxnode = node
    #             maxi = i
    #         else:
    #             if maxnode.val > node.val:
    #                 maxnode = node
    #                 maxi = i
    #     if maxnode is None:
    #         return maxnode
    #     # print '---', maxnode.val

    #     lists[maxi] = maxnode.next
    #     maxnode.next = self.mergeKLists(lists)
    #     return maxnode


def printlist(mylists):
    if mylists is None:
        return
    print mylists.val
    printlist(mylists.next)

if __name__ == '__main__':
    b = ListNode(1)
    b.next = ListNode(4)
    b.next.next = ListNode(8)
    e = ListNode(2)
    e.next = ListNode(9)
    e.next.next = ListNode(14)
    t = ListNode(3)
    t.next = ListNode(90)
    v = ListNode(-10)
    v.next = ListNode(100)
    sol = Solution()
    res = sol.mergeKLists([b, e, t, v])
    res = sol.mergeKLists([None])
    print res
    printlist(res)

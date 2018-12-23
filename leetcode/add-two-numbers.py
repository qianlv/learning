# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

    def add(self, listnode):
        listnode.next = self
        return listnode


class Solution:
    # @param {ListNode} l1
    # @param {ListNode} l2
    # @return {ListNode}
    def addTwoNumbers(self, l1, l2):
        # l1 = self.reverse(l1)
        # l2 = self.reverse(l2)
        p1 = l1
        p2 = l2
        inc = 0
        res = None
        while p1 and p2:
            val = p1.val + p2.val + inc
            inc = val / 10
            res = self.insert(res, val % 10)
            p1 = p1.next
            p2 = p2.next

        while p1:
            val = p1.val + inc
            inc = val / 10
            res = self.insert(res, val % 10)
            p1 = p1.next

        while p2:
            val = p2.val + inc
            inc = val / 10
            res = self.insert(res, val % 10)
            p2 = p2.next

        if inc:
            val = inc
            res = self.insert(res, val % 10)

        self.prin(res)
        return self.reverse(res)

    def addTwoNumbers1(self, l1, l2):
        res = cur = ListNode(0)
        inc = 0
        while l1 or l2:
            val1 = l1.val if l1 else 0
            val2 = l2.val if l2 else 0
            cur.next = ListNode((val1 + val2 + inc) % 10)
            cur = cur.next
            inc = (val1 + val2 + inc) / 10
            l1 = l1.next if l1 else l1
            l2 = l2.next if l2 else l2

        if inc:
            cur.next = ListNode(inc)
        return res.next

    def insert(self, l, val):
        p = ListNode(val)
        p.next = l
        return p

    def reverse(self, li):
        next_ptr = li.next
        li.next = None
        ptr = None
        while next_ptr:
            ptr = next_ptr.next
            next_ptr.next = li
            li = next_ptr
            next_ptr = ptr
        return li

    def prin(self, li):
        ptr = li
        while ptr:
            print ptr.val
            ptr = ptr.next


if __name__ == '__main__':
    sol = Solution()
    l1 = ListNode(5)
    l2 = ListNode(5)
    sol.addTwoNumbers(l1, l2)

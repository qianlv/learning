# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None


class ListNode(object):
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution(object):
    def removeNthFromEnd(self, head, n):
        """
        :type head: ListNode
        :type n: int
        :rtype: ListNode
        """
        tmp = head
        pre = None
        nlen = 0
        while tmp:
            nlen += 1
            tmp = tmp.next
        tmp = head

        n = nlen - n + 1
        while tmp:
            n -= 1
            if n == 0:
                if pre is None:
                    head = head.next
                else:
                    pre.next = tmp.next
            pre = tmp
            tmp = tmp.next

        return head


def printList(head):
    if not head:
        return
    print head.val
    printList(head.next)

if __name__ == '__main__':
    head = ListNode(2)
    head.next = ListNode(3)
    head.next.next = ListNode(4)
    sol = Solution()
    chead = sol.removeNthFromEnd(head, 1)
    printList(chead)

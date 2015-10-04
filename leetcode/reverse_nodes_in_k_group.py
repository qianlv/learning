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
    def reverseKGroup(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        tmphead = head
        tail = None
        while True:
            step = k
            tmp = tmphead
            while step > 0 and tmp:
                tmp = tmp.next
                step -= 1
            if step == 0:
                h, n, t = self.reverseK(tmphead, k)
                if tail is not None:
                    tail.next = h
                else:
                    head = h
                tmphead = n
                tail = t
            else:
                if tail is not None:
                    tail.next = tmphead
                break
        return head

    def reverseK(self, head, k):
        ''' return (head, nextk, tail)
        '''
        pre = None
        cur = head
        while k:
            nex = cur.next
            cur.next = pre
            pre = cur
            cur = nex
            k -= 1
        return (pre, cur, head)


def printlist(head):
    if head is None:
        return
    print head.val
    printlist(head.next)

if __name__ == '__main__':
    b = ListNode(1)
    b.next = ListNode(2)
    b.next.next = ListNode(3)
    b.next.next.next = ListNode(4)
    b.next.next.next.next = ListNode(5)
    sol = Solution()
    head = sol.reverseKGroup(b, 2)
    printlist(head)

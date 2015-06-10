#!/usr/bin/python
#encoding=utf-8

# 优先队列
import heapq
# 最大优先队列(默认最小优先队列)
# 其中 i 优先级相同情况下先入队列的在前,
# 也避免对于本身值得比较
class prioq(object):
    def __init__(self):
        self.q = []
        self.i = 0
    def push(self, item, cost):
        heapq.heappush(self.q, (-cost, self.i, item))
        self.i += 1
    def pop(self):
        return heapq.heappop(self.q)[-1]
# 获取序列中最小的几个元素
# 等价的heapq.nlargest(n, iteratable, key=None) = sorted(iteratable, key = key, reverse = True)[:n]
# heapq.nsmall(n, iteratable, key = None) = sorted(iteratable, key = key)[:n]
# iteratable 可迭代对象
def isorted(data):
    data = list(data)
    # data 要保证为列表
    heapq.heapify(data)
    while data:
        yield heapq.heappop(data)

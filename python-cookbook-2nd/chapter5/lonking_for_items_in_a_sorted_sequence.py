#!/usr/bin/python
#encoding=utf-8

import bisect
L = [0, 1, 2, 2, 3, 3, 5]
# L 需要已经排序(从小到大)
# bisect.bisect_right(L, x) 返回列表L中第一个大于x的位置
# bisect.bisect_left(L, x) 返回列表L中第一大于等于
# 按上述情况位置插入原列表
# bisect.insort_right(L, x)
# bisect.insort_left(L, x)
x_insert_point_right = bisect.bisect_right(L, 2)
x_insert_point_left = bisect.bisect_left(L, 2)
print x_insert_point_right
print x_insert_point_left

# 判断一个元素是否出现在列表中
x = 2
x_is_present = L[x_insert_point_right - 1: x_insert_point_right] == [x]
print x_is_present

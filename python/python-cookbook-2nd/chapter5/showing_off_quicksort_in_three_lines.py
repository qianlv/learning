#!/usr/bin/python
#encoding=utf-8

# L[0], L[0:1]的区别L[0]是一个L的元素值，L[0:1] 是一个列表
def quicksort(L):
    if len(L) <= 1: return L
    return quicksort([ lt for lt in L[1:] if lt < L[0] ]) + L[0:1] + quicksort([ rt for rt in L[1:] if rt >= L[0] ])
import random
def quicksort_another(L):
    if len(L) <= 1: return L
    pivot = random.choice(L)
    def lt(x): return x < pivot
    def gt(x): return x >= pivot
    return quicksort_another(filter(lt, L)) + quicksort_another(filter(gt, L))
def qs_test(quicksort, length):
    joe = range(length)
    random.shuffle(joe)
    qsjoe = quicksort(joe)
    for i in range(len(qsjoe)):
        assert qsjoe[i] == i, 'quicksort is broken at %d!' % i
# 本来想写3行归并的，结果WTF了, 写了这么多行
def merge(lt, rt):
    if not lt: return rt
    if not rt: return lt
    lnext = iter(lt).next
    rnext = iter(rt).next
    l = lnext()
    r = rnext()
    ans = []
    while True:
        if l < r:
            ans.append(l)
            try:
                l = lnext()
            except StopIteration:
                while True:
                    ans.append(r)
                    try:
                        r = rnext()
                    except StopIteration:
                        break
                break
        else:
            ans.append(r)
            try:
                r = rnext()
            except StopIteration:
                while True:
                    ans.append(l)
                    try:
                        l = lnext()
                    except StopIteration:
                        break
                break
    return ans
def merge_sort(L):
    if len(L) <= 1: return L
    le = len(L) / 2
    lt = merge_sort(L[0:le])
    rt = merge_sort(L[le:])
    return merge(lt, rt)

if __name__ == '__main__':
    L = [1,2,-1,0,3,2,1,10]
    print quicksort(L)
    print merge_sort(L)
    for le in range(100):
        qs_test(merge_sort, 10000 * le)
    for le in range(1):
        qs_test(quicksort_another, 10000 * le)


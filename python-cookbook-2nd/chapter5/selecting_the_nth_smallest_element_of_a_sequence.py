#!/usr/bin/python
#encoding=utf-8

import random
def select(data, n):
    data = list(data)
    if n < 0:
        n += len(data)
    if not 0 <= n < len(data):
        raise ValueError, "can't get rank %d out of %d" % (n, len(data))
    while True:
        pivot = random.choice(data)
        pcount = 0
        under, over = [], []
        uappend, oappend = under.append, over.append
        for item in data:
            if item < pivot:
                uappend(item)
            elif item > pivot:
                oappend(item)
            else:
                pcount += 1
        nnumber = len(under)
        if n < nnumber:
            data = under
        elif n < nnumber + pcount:
            return pivot
        else:
            data = over
            n -= nnumber + pcount
if __name__ == '__main__':
    li = [2, 3, 4, -1, 0, 3]
    print select(li, 2)
    print select(li, 1)
    print select(li, 0)

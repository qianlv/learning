#!/usr/bin/python
#encoding=utf-8

import os, itertools

def all_equal(elements):
    first_element = elements[0]
    for element in elements[1:]:
        if not first_element is element:
            return False
    return True
# 其他方式
def all_equal_1(elements):
    return len(dict.fromkeys(elements)) == 1
def all_equal_2(elements):
    return len(set(elements)) == 1

# 序列公共前缀
def common_suffix(*sequences):
    if not sequences: return [], []
    common = []
    for elements in itertools.izip(*sequences):
        if not all_equal(elements) : break
        common.append(elements[0])
    return common, [ sequence[len(common):] for sequence in sequences ]

def relpath(p1, p2, sep = os.path.sep, pardir = os.path.pardir):
    common, (u1, u2) = common_suffix(p1.split(sep), p2.split(sep))
    if not common:
        return p2
    return sep.join([pardir] * len(u1) + u2)

# os.path.commonprefix 求公共前缀
def my_common_suffix(*sequences):
    common = os.path.commonprefix(sequences)
    return common, [ sequence[len(common):] for sequence in sequences ]
def my_relpath(p1, p2, sep = os.path.sep, pardir = os.path.pardir):
    common, (u1, u2) = my_common_suffix(p1.split(sep), p2.split(sep))
    if not common:
        return p2
    return sep.join([pardir] * len(u1) + u2)
    
def test(p1, p2, sep = os.path.sep):
    print 'from', p1, 'to', p2, '->', relpath(p1, p2, sep)
    print 'from', p1, 'to', p2, '->', my_relpath(p1, p2, sep)

if __name__ == '__main__':
    test('/a/b/c/d', '/a/b/c1/d1/', '/')
    test('/a/b/c/d', '/a/b/c/d/', '/')
    test('c:/x/y/z', 'd:x/y/z', '/')

    


#!/usr/bin/python
#encoding=utf-8

# 使用列表中的元素交替作为键值和对应值创建一个字典

def dictFromList(keysAndValues):
    return dict(zip(keysAndValues[0::2], keysAndValues[1::2]))

# 适用于可迭代对象
def pairwise(iterable):
    itnext = iter(iterable).next
    while True:
        yield itnext(), itnext()
# 效率比较低
def pairwise_slow(iterable):
    it = iter(iterable)
    while True:
        yield it.next(), it.next()
def dictFromSequence(seq):
    return dict(pairwise(seq))

if __name__ == '__main__':
    print dictFromSequence('abcdefghi')

#!/usr/bin/python
#encoding=utf-8

def is_list_or_tuple(x):
    return isinstance(x, (list,tuple))

# a predicate that will expand just about any iterable except strings (plain and Unicode)
# 一个断定: 展开任意可以迭代的对象，除了字符串(plain和unicode)
# To identify whether an object is iterable,we just need to try calling the built-in iter
# on that object: the call raises TypeError if the object is not iterable. To identify
# whether an object is string-like,we simply check whether the object is an instance of
# basestring,since isinstance(obj, basestring) is True when obj is an instance of any
# subclass of basestring—that is,any string-like type
# 判断是否可以对象可以迭代，排除字符串
def nonstring_iterator(obj):
    try: iter(obj)
    except TypeError: return False
    else: return not isinstance(obj, basestring)
# 展开一个嵌套序列
def flatten(sequence, to_expend = is_list_or_tuple):
    for item in sequence:
        if to_expend(item):
            for subitem in flatten(item, to_expend):
                yield subitem
        else:
            yield item

# 非递归版本
# 关键点是: 迭代器可以保持中断状态,记录迭代状态
# 例如: 
it = iter([1,2,3,4]) 
for i in it:
    print i
    break
for i in it:
    print i

def nonrecursive_flatter(sequence, to_expend = is_list_or_tuple):
    # 包含多个迭代器的列表
    iterators = [iter(sequence)]
    while iterators:
        for item in iterators[-1]:
            if to_expend(item):
                iterators.append(iter(item))
                break
            else:
                yield item
        else:
            iterators.pop()
        
    
if __name__ == '__main__':
    my_list = ['1abc', 2, [ 3, [3, 4], 'a', [[]], [ 3,[ 3,4 ] ] ] ]
    for i in flatten(my_list, nonstring_iterator):
        print i,
    print ''
    for i in nonrecursive_flatter(my_list, nonstring_iterator):
        print i,

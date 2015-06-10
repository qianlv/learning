#!/usr/bin/python
#encoding=utf-8

# 对象赋值是原对象的引用
print u'赋值:'
a = [1, 2, 3]
b = a
b.append(a)
print a is b # True

# 浅拷贝: it copies an object,but for each attribute 
# or item of the object,it continues to share references
# ,which is faster and saves memory. (对象内部的属性和内容仍为引用
# 原对象)
# 方式: copy.copy, 或已经知道类型为Type, mycopy = Type(my), 
# 例如 列表L，调用list(L), 字典d, dict(d) 或 d.copy()
# copy.copy 对于任意类型或类的实例都可以, 
# 定制自己的类的浅拷贝方式，要提供特殊的__copy__方法, 深拷贝需要__deepcopy__方法

import copy
lists = [ ['a'], [1, 2, 3], [3, 4] ]
lists_copy = copy.copy(lists)
lists_copy[1].append('a')
# Python中的对象包含三要素：id、type、value
# 其中id用来唯一标识一个对象，type标识对象的类型，value是对象的值
# is判断的是a对象是否就是b对象，是通过id来判断的
# ==判断的是a对象的值是否和b对象的值相等，是通过value来判断的
print u'浅拷贝:'
print lists is lists_copy # False
print lists == lists_copy # True
lists_copy.append('different')
print lists == lists_copy # False

# 没有必要拷贝那些不可改变的对象(字符串, 数字, 元组等)
# 拷贝后也是原对象, 但是无害
print u'不可改变对象拷贝:'
s = 'cat'
t = copy.copy(s)
print s is t

# copy.deepcopy 深拷贝
print u'深拷贝:'
list_deep_copy = copy.deepcopy(lists)
list_deep_copy[1].append('a')
print lists is list_deep_copy
print lists == list_deep_copy

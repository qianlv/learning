#!/usr/bin/python
#encoding=utf-8

# 在无须共享引用的条件下创建列表的列表
# 避免隐式的引用共享

multi = [ [0] * 5 ] * 3
print multi 
multi[0][0] = 'oops'
print multi
# [ [ 'oops', 0, 0, 0, 0 ],[ 'oops', 0, 0, 0, 0],[ 'oops', 0, 0, 0, 0 ] ] 

# 等价方式
row = [0] * 5 # row 列表中的5个子项都是引用0
multi = row * 3 # multi 列表中的3个子项都是引用row
# 解释: 在row创建中， 有无引用被复制完全不重要， 因为被引用的
# 是数字, 而数字不可改变，换句话说，如果对象是不可改变的，则
# 对象和对对象的引用实际没有区别。
# multi创建中，包含了3个对[row] 内容引用，而其内容则是对一个
# 列表的引用。因此修改时候其他3个引用也改变了，甚至row也改变

# 解决方法:
multilist_method1 = [ [ 0 for col in range(5) ] for row in range(3) ]
multilist_method2 = [ [0] * 5 for row in range(3) ]
multilist_method1[0][0] = 'abc'
multilist_method2[0][0] = 'edf'
print multilist_method1
print multilist_method2


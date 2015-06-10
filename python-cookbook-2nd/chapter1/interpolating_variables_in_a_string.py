#!/usr/bin/python
#encoding=utf-8

import string
new_style = string.Template("this is $thing")
print new_style.substitute({'thing':5})
print new_style.substitute({'thing':'test'})
print new_style.substitute(thing = 5)
print new_style.substitute(thing = 'test')

# 通过本地变量设置字典, locals() 创建

msg = string.Template('the square of $number is $square')
for number in range(10):
    print msg.substitute(locals(), square = number * number)
# 为防止字典的条目和关键字显式传递的值发生冲突, 关键字参数优先
msg = string.Template('an $obj $msg')
adj = 'interesting'
print 

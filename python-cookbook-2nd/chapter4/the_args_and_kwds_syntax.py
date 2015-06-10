#!/usr/bin/python
#encoding=utf-8

# *args 用于接受或传递任意基于位置的参数语法, 绑定为一个元组
# **kwds 用于接受或传递任意命名的参数的语法, 绑定为字典
def change_arg(*args):
    print args
def change_kwds(**kwds):
    print kwds
def test(*args, **kwds):
    print args, kwds
    # 注意此次区别, args 为一个元组, *args 又把元组变为位置参数
    # kwds 与 **kwds 类似
    change_arg(args)
    change_arg(*args)
    #change_kwds(kwds) 报错,因为kwds是一个字典，为位置参数
    change_kwds(**kwds)
test(1, 2, 3, w = 3)

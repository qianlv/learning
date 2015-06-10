#!/usr/bin/python
#encoding=utf-8

# 获取字典子集
def sub_dict(somedict, somekeys, default = None):
    return dict((key, somedict.get(key, default)) for key in somekeys)

# 获取字典子集且删除原字典
def sub_dict_remove(somedict, somekeys, default = None):
    return dict((key, somedict.pop(key, default)) for key in somekeys)

# 如果键值不存在抛出异常
def sub_dict_except(somedict, somekeys, default = None):
    return dict((key, somedict[key]) for key in somekeys)
def sub_dict_remove_except(somedict, somekeys, default = None):
    return dict((key, somedict.pop(key)) for key in somekeys)

# 忽略键值不存在的情况
def sub_dict_ignore(somedict, somekeys, default = None):
    return dict((key, somedict[key]) for key in somekeys if key in somedict)
def sub_dict_remove_ignore(somedict, somekeys, default = None):
    return dict((key, somedict.pop(key)) for key in somekeys if key in somedict)

if __name__ == '__main__':
    d = dict(a = 1, b = 2, c = 3)
    print sub_dict(d, 'abe', 'no found'), d
    print sub_dict_remove(d, 'abe', 'no found'), d
    print '--------------------------------------'
    d = dict(a = 1, b = 2, c = 3)
    print sub_dict_ignore(d, 'abe', 'no found'), d
    print sub_dict_remove_ignore(d, 'abe', 'no found'), d

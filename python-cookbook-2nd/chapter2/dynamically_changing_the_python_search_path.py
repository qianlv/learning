#!/usr/bin/python
#encoding=utf-8

import os, sys

def addSysPath(newpath):
    # 判读路径是否存在
    if not os.path.exists(newpath): return -1
    # 标准化路径， window下大写不敏感
    # window 下转成小写 
    newpath = os.path.abspath(newpath)
    if sys.platform == 'win32':
        newpath = newpath.lower()
    for x in sys.path:
        x = os.path.abspath(x)
        if sys.platform == 'win32':
            x = x.lower()
        if x in (x, x + os.sep):
            return 0
    sys.path.append(newpath)
    # 插入前面用 
    # sys.path.insert(0, newpath)
    return 1

if __name__ == '__main__':
    print 'before:'
    for x in sys.path:
        print x
    if sys.platform == 'win32':
        print addSysPath('C:\\Temp')
        print addSysPath('C:\\temp')
    else:
        print addSysPath('/home/qianlv/git/python-cookbook-2nd/chapter2')
    print 'after'
    for x in sys.path:
        print x
    
        

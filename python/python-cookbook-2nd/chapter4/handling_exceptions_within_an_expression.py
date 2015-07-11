#!/usr/bin/python
#encoding=utf-8

def throws(t, f, *args, **kwds):
    ''' 如果f(*args, **kwds)抛出异常且其类型是t则返回True(如果t是元组的话,
       类型是t中的某项) '''
    try:
        f(*args, **kwds)
    except t:
        return True
    else:
        return False

some_file = 'some_file.txt'
data = [ float(line) for line in open(some_file)
                        if not throws(ValueError, float, line) ]
print data



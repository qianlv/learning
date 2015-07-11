#!/usr/bin/python
#encoding=utf-8

import itertools
# imap 创建一个迭代器，生成项 function(i1, i2, ..., iN)，其中 i1，i2...iN 分别来自迭代器 iter1，iter2 ... iterN，
# 如果 function 为 None，则返回 (i1, i2, ..., iN )形式的元组，只要提供的一个迭代器不再生成值，迭代就会停止。
def anyTrue(predicate, sequence):
    return True in itertools.imap(predicate, sequence)
# str.endswith(suffix[, start[, end]]) 如果str是否以suffix为后缀
def endWith(s, *endings):
    return anyTrue(s.endswith, endings)

if __name__ == '__main__':
    import os
    # 当前目录下后缀为'.jpg', '.py', '.cpp'的文件
    for filename in os.listdir('.'):
        if endWith(filename, '.jpg', '.py', '.cpp'):
            print filename



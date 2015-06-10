#!/usr/bin/python
#encoding=utf-8

import os

# 在不确定文本用什么换行符, 'rU' 指定通用换行符, 这样无论什么平台下的各种
# 换行符都被映射成'\n'
file_object = open("thefile.txt", 'rU')
# 不要把 open 的调用放入到 try/finally 语句的 try 子句中
# 因为如果在打开文件的时候就发生错误，那就没什么东西需要关闭,
# 没有什么东西绑定上去 
try:
    all_the_text = file_object.read()
    file_object.seek(0, os.SEEK_SET)

    # 逐行读取文本, 读出文本带'\n'
    list_of_all_the_lines = file_object.readlines()
    file_object.seek(0, os.SEEK_SET)
    print list_of_all_the_lines

    # 不带'\n'按行读取文本
    list_of_all_the_lines = file_object.read().splitlines()
    file_object.seek(0, os.SEEK_SET)
    print list_of_all_the_lines

    list_of_all_the_lines = file_object.read().split('\n')
    file_object.seek(0, os.SEEK_SET)
    print list_of_all_the_lines

    list_of_all_the_lines = [ L.rstrip() for L in file_object ]
    file_object.seek(0, os.SEEK_SET)
    print list_of_all_the_lines

    list_of_all_the_lines = [ L.rstrip('\n') for L in file_object ]
    file_object.seek(0, os.SEEK_SET)
    print list_of_all_the_lines
finally:
    file_object.close()

# 固定读取长度文本生成器
# yield 关键字不被允许出现在 try 子句中
def read_file_by_chunk(filename, chunksize = 100):
    file_object = open(filename, 'rb')
    while True:
        chunk = file_object.read(chunksize)
        if not chunk:
            break
        yield chunk
    file_object.close()


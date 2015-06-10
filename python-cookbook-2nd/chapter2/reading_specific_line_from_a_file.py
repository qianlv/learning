#!/usr/bin/python
#encoding=utf-8

# 使用 linecache 获取指定行, 当你要对文件进行多次读取时,
# lincache 会缓存信息避免重复工作
# linecache.getline(thefilepath, lineno) 
# linecache.clearcache() 释放缓存
# linecache.checkcache([filename]) 磁盘文件发生变化,确保缓存中存储为最新信息
import linecache
theline = linecache.getline('thefile.txt', 3)
print theline

# 如果文本太大，且你只需其中一行, 可以显示循环获取
def getline(thefilepath, desired_line_number):
    if desired_line_number < 1 : return ''
    for current_line_number, line in enumerate(open(thefilepath, 'rU')):
        if current_line_number == desired_line_number - 1 : return line
    return ''


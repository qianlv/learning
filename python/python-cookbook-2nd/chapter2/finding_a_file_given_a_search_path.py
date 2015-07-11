#!/usr/bin/python
#encoding=utf-8

import os

# os.pathseq 搜索路径分隔符(像 PATH), ':' for POSIX or ';' for Windows
def search_file(filename, search_path, pathsep = os.pathsep):
    # 搜索给定目录下的文件
    for path in search_path.split(pathsep):
        candidate = os.path.join(path, filename)
        if os.path.isfile(candidate):
            return os.path.abspath(candidate)
    return None

if __name__ == '__main__':
    search_path = '/bin' + os.pathsep + '/usr/bin'
    find_file = search_file('ls', search_path)
    if find_file:
        print "File 'ls' found at %s" % find_file
    else:
        print "File 'ls' not found"

#!/usr/bin/python
#encoding=utf-8

import os, glob

# glob.glob(pathname) 返回所有与 pathname 匹配目录文件
# pathname 可以绝对路径或相对路径, 也可以包含 shell-style 统配符 
def all_files(pattern, search_path, pathsep = os.pathsep):
    for path in search_path.split(pathsep):
        for match in glob.glob(os.path.join(path, pattern)):
            yield match

if __name__ == '__main__':
    import sys
    if len(sys.argv) != 2 or sys.argv[1].startswith('-'):
        print 'Use: %s <pattern>' % sys.argv[0]
        sys.exit(1)
    matches = all_files(sys.argv[1], os.environ['PATH'])
    for match in matches:
        print match

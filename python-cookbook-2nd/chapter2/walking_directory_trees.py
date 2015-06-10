#!/usr/bin/python
#encoding=utf-8

import os, fnmatch
# root 要遍历的目录,
# patterns 文件名匹配模式(unix shell-style 通配符),用分号分隔.
# single_level 是否只检查单一目录
# yield_folders 是否显示目录
def all_files(root, patterns='*', single_level=False, yield_folders=False):
    patterns = patterns.split(';')
    for path, subdirs, files in os.walk(root):
        if yield_folders:
            files.extend(subdirs)
        files.sort()
        for name in files:
            for pattern in patterns:
                if fnmatch.fnmatch(name, pattern):
                    yield os.path.join(path, name)
                    break
        if single_level:
            break

if __name__ == '__main__':
    for name in all_files('/home/qianlv/Documents/C++', yield_folders=True):
        print name

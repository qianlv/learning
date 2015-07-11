#!/usr/bin/python
#encoding=utf-8

import os, sys

# 修改目录下文件的拓展名
def swapextensions(dir, before, after):
    if before[:1] != '.':
        before = '.' + before
    thelen = -len(before)
    if after[:1] != '.':
        after = '.' + after
    for path, subdirs, files in os.walk(dir):
        ischange = False
        path = os.path.abspath(path)
        for oldfile in files:
            if oldfile[thelen:] == before:
                oldfile = os.path.join(path, oldfile)
                newfile = oldfile[:thelen] + after
                os.rename(oldfile, newfile)
                # 输出修改文件 
                if not ischange:
                    ischange = True
                    print path + ':'
                print os.path.basename(oldfile) + ' -> ' + os.path.basename(newfile)

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print 'Usage: %s rootdir before after' % os.path.basename(sys.argv[0])
        sys.exit(100)
    swapextensions(sys.argv[1], sys.argv[2], sys.argv[3])



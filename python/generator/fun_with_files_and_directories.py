# encoding=utf-8

import os
import fnmatch
import re
import gzip
import bz2


def gen_find(filepat, top):
    for path, dirlist, filelist in os.walk(top):
        # path     : current directory
        # dirlist  : List of subdirectiories
        # filelist : List of files
        for name in fnmatch.filter(filelist, filepat):
            yield os.path.join(path, name)


def gen_open(filenames):
    for name in filenames:
        if name.endswith('.gz'):
            yield gzip.open(name)
        elif name.endswith('.bz2'):
            yield bz2.BZ2File(name)
        else:
            yield open(name)


def gen_cat(sources):
    for s in sources:
        for item in s:
            yield item


def gen_grep(pat, lines):
    patc = re.compile(pat)
    for line in lines:
        if patc.search(line):
            yield line


def count_transferred_bytes():
    lognames = gen_find('rxgx*', '/home/qianlv/Git/learning/python/generator/')
    logfiles = gen_open(lognames)
    loglines = gen_cat(logfiles)
    # for line in loglines:
    #     print line
    pat = r'^([\s\S]+)$'
    patlines = gen_grep(pat, loglines)
    logpats = r'(\S+) (\S+) (\S+) \[(.*?)\] ' \
        '"(.*?)" (\S+) (\S+) "(\S+)" "(.*?)"'
    logpat = re.compile(logpats)
    bytenum = (logpat.split(line)[7] for line in patlines)
    bytes = (int(x) for x in bytenum if x != '-')
    print sum(bytes)
    # print logpat.split(
    # '''192.168.19.187 - - [19/Sep/2015:02:03:13 +0800] "-" 400 0 "-" "-"''')
    # print logpat.split('''10.0.128.228 - - [18/Sep/2015:03:08:24 +0800]'''
    #           '''"GET /cc/report?zid=1&online=0 HTTP/1.1" 200 5 "-" "-"''')
    # print logpat.split(u'''192.168.18.11 - - [18/Sep/2015:16:05:17 +0800] "GET /pay/callback?req='''
    # '''{\x22u\x22:4219471249, \x22s\x22:7, \x22p\x22:10002}&p=1965575001|1382124391|5500|0&time=0&sign= HTTP/1.1"'''
    # '''400 5 "-" "UnityPlayer/4.6.0f3 (http://unity3d.com)"''')
    # for line in patlines:
    #     try:
    #         logpat.split(line)[-5]
    #     except Exception as e:
    #         print logpat.split(line)
    #         print line, e

if __name__ == '__main__':
    pyfiles = gen_find('*.py', '/home/qianlv/Git/learning/')
    # for name in pyfiles:
    #     print name
    count_transferred_bytes()

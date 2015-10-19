# encoding=utf-8

import re
from fun_with_files_and_directories import gen_find, gen_open, gen_cat


def lines_from_dir(filepat, dirname):
    names = gen_find(filepat, dirname)
    files = gen_open(names)
    lines = gen_cat(files)
    return lines


def field_map(dictseq, name, func):
    for d in dictseq:
        d[name] = func(d[name])
        yield d


def nginx_log(lines):
    logpats = r'(\S+) (\S+) (\S+) \[(.*?)\] ' \
        '"(.*?)" (\S+) (\S+) "(\S+)" "(.*?)"'
    logpat = re.compile(logpats)
    groups = (logpat.match(line) for line in lines)
    tuples = (g.groups() for g in groups if g)
    colnames = ('hosts', 'decollator', 'user', 'datetime', 'request', 'status', 'bytes', 'referer', 'user-agent')
    log = (dict(zip(colnames, t)) for t in tuples)
    log = field_map(log, 'status', int)
    log = field_map(log, 'bytes',
                    lambda s: int(s) if s != '-' else 0)
    return log

if __name__ == '__main__':
    lines = lines_from_dir('rxgx*', '/home/qianlv/Git/learning/python/generator/')
    log = nginx_log(lines)

    # stat404 = set(r['request'] for r in log if r['status'] == 404)
    # print stat404

    # large = (r for r in log if r['bytes'] > 10000)
    # for r in large:
    #     print r['request'], r['bytes']

    # # find the largest data transfer
    # print '%d %s' % max((r['bytes'], r['request']) for r in log)

    # collect all unique host IP address
    hosts = set(r['hosts'] for r in log)
    print hosts
    import socket
    for host in hosts:
        try:
            print socket.gethostbyaddr(host)
        except socket.herror:
            print host

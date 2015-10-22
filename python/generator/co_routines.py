# encoding=utf-8

from processing_infinite_data import follow
from parsing_and_prcessing_data import nginx_log


# Co-routines
def recv_count():
    try:
        while True:
            n = (yield)
            print "T-minus", n
    except GeneratorExit:
        print "Kaboom!"

r = recv_count()
r.next()    # this is must be called
for i in range(5, 0, -1):
    r.send(i)
r.close()


# 通过decoration处理到next调用
def consumer(func):
    def start(*args, **kwargs):
        c = func(*args, **kwargs)
        c.next()
        return c
    return start


@consumer
def recv_count2():
    try:
        while True:
            n = (yield)
            print "T-minus", n
    except GeneratorExit:
        print "Kaboom!"

r = recv_count2()
for i in range(0, 5):
    r.send(i)


def broadcast(source, consumers):
    for item in source:
        for c in consumers:
            c.send(item)


@consumer
def find_404():
    while True:
        r = (yield)
        if r['status'] == 404:
            print r['status'], r['datetime'], r['request']


@consumer
def bytes_transferred():
    total = 0
    while True:
        r = (yield)
        total += r['bytes']
        print "Total bytes", total

lines = follow(open('rxgx.log'))
log = nginx_log(lines)
broadcast(log, [find_404(), bytes_transferred()])

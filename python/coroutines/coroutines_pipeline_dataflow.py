# encoding=utf-8

import time
from coroutine import coroutine


# source
def follow(thefile, target):
    thefile.seek(0, 2)
    while True:
        line = thefile.readline()
        if not line:
            time.sleep(0.1)
            continue
        target.send(line)


# sink
@coroutine
def printer():
    while True:
        line = (yield)
        print line,

# f = open("rxgx.log")
# follow(f, printer())


# Intermediate stages
@coroutine
def grep(pattern, target):
    while True:
        line = (yield)
        if pattern in line:
            target.send(line)

# f = open("rxgx.log")
# follow(f,
#        grep('python',
#        printer()))


# 传输给多个目标
@coroutine
def broadcast(targets):
    while True:
        item = (yield)
        for target in targets:
            target.send(item)

if __name__ == '__main__':
    f = open("rxgx.log")
    # follow(f,
    #        broadcast([grep('python', printer()),
    #                   grep('ply', printer()),
    #                   grep('swig', printer())])
    #     )

    p = printer()
    follow(
        f,
        broadcast([grep('python', p),
                   grep('ply', p),
                   grep('swig', p)])
        )

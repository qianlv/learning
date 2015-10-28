# encoding=utf-8

import time


# generators
def follow(thefile):
    thefile.seek(0.2)
    while True:
        line = thefile.readline()
        if not line:
            time.sleep(0.1)
            continue
        yield line


def grep1(pattern, lines):
    for line in lines:
        if pattern in line:
            yield line

# logfile = open('rxgx.log')
# loglines = follow(logfile)
# pylines = grep1('python', loglines)
#
# for line in pylines:
#     print line,


def coroutine(func):
    def start(*args, **kwargs):
        cr = func(*args, **kwargs)
        cr.next()
        return cr
    return start


@coroutine
def grep(pattern):
    print "Looking for {} ".format(pattern)
    try:
        while True:
            line = (yield)
            if pattern in line:
                print line
    except GeneratorExit:
        print "Going away. Goodbye"

r = grep('python')
r.send("Yeah, but no, but yeah, but no")
r.send("Yeah, but no, but yeah, but no, python")
r.close()   # can be caught(GeneratorExit) or Garbage(when progress exit) also calls close()
r.throw(RuntimeError, "You're hosed")

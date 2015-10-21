# encoding=utf-8

import math
import time
import signal
import threading
from processing_infinite_data import follow
from parsing_and_prcessing_data import nginx_log


# -------------------------------------#
# Creating Generators
def generate(func):
    def gen_func(s):
        for item in s:
            yield func(item)
    return gen_func

gen_sqrt = generate(math.sqrt)
for x in gen_sqrt(xrange(10)):
    print x
# -------------------------------------#


# -------------------------------------#
# Debug
def trace(source):
    for item in source:
        print item
        yield item

lines = follow(open('rxgx.log'))
log = trace(nginx_log(lines))
r404 = trace(r for r in log if r['status'] == 404)
# for r in r404:
#     print r
# -------------------------------------#


# -------------------------------------#
class storelast(object):
    def __init__(self, source):
        self.source = source

    def next(self):
        item = self.source.next()
        self.last = item
        return item

    def __iter__(self):
        return self

lines = storelast(follow(open('rxgx.log')))
log = nginx_log(lines)
# for r in log:
#     print r
#     print lines.last
# -------------------------------------#


# -------------------------------------#
# GeneratorExit
def follow_e(thefile):
    thefile.seek(0, 2)
    try:
        while True:
            line = thefile.readline()
            if not line:
                time.sleep(0.2)
                continue
            yield line
    except GeneratorExit:
        # You can cleanup source(if need)
        print 'Follow: Shutting down'


# Ignore GeneratorExit
def follow_i(thefile):
    thefile.seek(0, 2)
    while True:
        try:
            line = thefile.readline()
            if not line:
                time.sleep(0.2)
                continue
            yield line
        except GeneratorExit:
            # Get RunTimeError
            print 'Ignore GeneratorExit'

# lines = follow(open('rxgx.log'))
# lines = follow_e(open('rxgx.log'))
# lines = follow_i(open('rxgx.log'))
# for i, line in enumerate(lines):
#     print line
#     if i == 2:
#         lines.close()
# -------------------------------------#

# -------------------------------------#
# Another thread shutdown a generator
lines = follow(open('rxgx.log'))


def sleep_and_close(s):
    time.sleep(s)
    lines.close()

# threading.Thread(target=sleep_and_close, args=(2,)).start()
# for line in lines:
#     print line,
# -------------------------------------#


# -------------------------------------#
# Use siganl to shut down generator
def sigusr1(signo, frame):
    print 'Closing it down'
    lines.close()

# signal.signal(signal.SIGUSR1, sigusr1)
# for line in lines:
#     print line
# -------------------------------------#


# -------------------------------------#
# ShutDown a generator by instrumenting with a flag
def follow_s(thefile, shutdown=None):
    thefile.seek(0, 2)
    while True:
        if shutdown and shutdown.isSet():
            break
        line = thefile.readline()
        if not line:
            time.sleep(0.2)
            continue
        yield line

shutdown = threading.Event()


def sigusr2(signo, frame):
    print 'Closing it down'
    shutdown.set()

signal.signal(signal.SIGUSR1, sigusr2)
lines = follow_s(open('rxgx.log'), shutdown)
for line in lines:
    print line
# -------------------------------------#

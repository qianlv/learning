# encoding=utf-8

from processing_infinite_data import follow
import socket
import pickle
import Queue
import threading
import itertools


# 广播多个consumers
def broadcast(source, consumers):
    for item in source:
        for c in consumers:
            c.send(item)


class Consumer(object):
    def send(self, item):
        print self, "got", item


class NetConsumer(object):
    def __init__(self, addr):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect(addr)

    def send(self, item):
        ptime = pickle.dumps(item)
        self.s.sendall(ptime)

    def close(self):
        self.s.close()


class Stat404(NetConsumer):
    def send(self, item):
        if item['status'] == 404:
            NetConsumer.send(self, item)


class ConsumerThread(threading.Thread):
    def __init__(self, target):
        threading.Thread.__init__(self)
        self.setDaemon(True)
        self.in_queue = Queue.Queue()
        self.target = target

    def send(self, item):
        self.in_queue.put(item)

    def generate(self):
        while True:
            item = self.in_queue.get()
            yield item

    def run(self):
        self.target(self.generate())


def find_404(log):
    for r in (r for r in log if r['status'] == 404):
        print r['status'], r['datetime'], r['request']


def bytes_transferred(log):
    total = 0
    for r in log:
        total += r['bytes']
        print "Total bytes", total


# 串行, 多个数据源
def concatenate(sources):
    for s in sources:
        for item in s:
            yield item


# 并行
def parallel(s1, s2, s3):
    return itertools.izip(s1, s2, s3)


def gen_multiplex(genlist):
    item_q = Queue.Queue()

    def run_one(source):
        for item in source:
            item_q.put(item)

    def run_all():
        thrlist = []
        for source in genlist:
            t = threading.Thread(target=run_one, args=(source,))
            t.start()
            thrlist.append(t)
        for t in thrlist:
            t.join()
        item_q.put(StopIteration)

    threading.Thread(target=run_all).start()
    while True:
        item = item_q.get()
        if item is StopIteration:
            return
        yield item

if __name__ == '__main__':
    # c1 = Consumer()
    # c2 = Consumer()
    # c3 = Consumer()
    # lines = follow(open('rxgx.log'))
    # log = nginx_log(lines)
    # broadcast(log, [c1, c2, c3])

    # stat404 = Stat404(('', 15000))
    # lines = follow(open('rxgx.log'))
    # log = nginx_log(lines)
    # broadcast(log, [stat404])

    # lines = follow(open('rxgx.log'))
    # log = nginx_log(lines)
    # t1 = ConsumerThread(find_404)
    # t1.start()
    # t2 = ConsumerThread(bytes_transferred)
    # t2.start()
    # broadcast(log, [t1, t2])

    log1 = follow(open('rxgx.log'))
    log2 = follow(open('rxgx.log-20150919.gz'))
    lines = gen_multiplex([log1, log2])
    for line in lines:
        print line

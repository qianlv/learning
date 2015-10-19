# encoding=utf-8

import socket
import select
import threading
import Queue


def receive_connection(addr):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(addr)
    s.listen(5)
    while True:
        client = s.accept()
        yield client


def receive_messages(addr, maxsize):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind(addr)
    while True:
        msg = s.recvfrom(maxsize)
        yield msg


def gen_events(socks):
    while True:
        rdr, wrt, err = select.select(socks, socks, socks, 0.1)
        # print socks
        for r in rdr:
            print threading.currentThread().getName(), r
            yield 'read', r
        for w in wrt:
            yield 'write', w
        for e in err:
            yield 'error', e


def acceptor(socketset, addr):
    for client, addr in receive_connection(addr):
        print threading.currentThread().getName(), client
        socketset.append(client)


def io_multiplexing():
    # acc_thr: 输入源接受客户端socket
    # 主线: I/O复用消费socket
    clientset = []

    acc_thr = threading.Thread(target=acceptor,
                               args=(clientset, ('', 12000)))
    acc_thr.setDaemon(True)
    acc_thr.start()
    for evt, s in gen_events(clientset):
        if evt == 'read':
            data = s.recv(1024)
            if not data:
                print "Closing", s
                s.close()
                clientset.remove(s)
            else:
                print s, data


def consume_queue(thequeue):
    while True:
        item = thequeue.get()
        if item is StopIteration:
            break
        yield item


def consumer(q):
    for item in consume_queue(q):
        print "Consumed", item
    print "Done"


def consuming_queue():
    in_q = Queue.Queue()
    con_thr = threading.Thread(target=consumer, args=(in_q,))
    con_thr.start()

    for i in xrange(100):
        in_q.put(i)
    in_q.put(StopIteration)

if __name__ == '__main__':
    # for client, addr in receive_connection(('', 8888)):
    #     print client
    #     client.send('Hello World\n')
    #     client.close()

    # for msg, addr in receive_messages(('', 8888), 1024):
    #     print msg, " from", addr
    consuming_queue()

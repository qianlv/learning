# encoding=utf-8

import socket

from sockwrap import Socket
from pyos8 import Scheduler
from pyos8 import NewTask


def handle_client(client, addr):
    print 'connection from', addr
    while True:
        data = yield client.recv(65536)
        if not data:
            break
        yield client.send(data)
    print 'Client closed'
    yield client.close()


def server(port):
    print "Server starting"
    rawsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    rawsock.bind(('', port))
    rawsock.listen(5)
    sock = Socket(rawsock)
    while True:
        client, addr = yield sock.accept()
        yield NewTask(handle_client(client, addr))

if __name__ == '__main__':
    sched = Scheduler()
    sched.new(server(45000))
    sched.mainloop()

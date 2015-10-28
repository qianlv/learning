# encoding=utf-8

import socket
from pyos6 import NewTask
from pyos6 import Scheduler


def handle_client(client, addr):
    print 'Connection from', addr
    while True:
        data = client.recv(65536)
        if not data:
            break
        client.send(data)
    client.close()
    print 'Client Close'
    yield                   # Make the function a generator/coroutine


def server(port):
    print 'Server starting'
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('', port))
    sock.listen(5)
    while True:
        client, addr = sock.accept()
        yield NewTask(handle_client(client, addr))


def alive():
    while True:
        print "I'm alive!"
        yield

if __name__ == '__main__':
    sched = Scheduler()
    sched.new(alive())
    sched.new(server(45000))
    sched.mainloop()

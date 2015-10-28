# encoding=utf-8

import socket
from pyos7 import NewTask
from pyos7 import Scheduler
from pyos7 import ReadWait
from pyos7 import WriteWait


def handle_client(client, addr):
    print 'Connection from', addr
    while True:
        yield ReadWait(client)
        data = client.recv(65536)
        if not data:
            break
        yield WriteWait(client)
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
        yield ReadWait(sock)
        print '---'
        client, addr = sock.accept()
        yield NewTask(handle_client(client, addr))


if __name__ == '__main__':
    sched = Scheduler()
    sched.new(server(45000))
    sched.mainloop()

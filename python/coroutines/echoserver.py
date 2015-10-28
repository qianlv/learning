# encoding=utf-8

import socket

from pyos8 import Scheduler
from pyos8 import NewTask
from pyos8 import Accept
from pyos8 import Recv
from pyos8 import Send


def handle_client(client, addr):
    print 'connection from', addr
    while True:
        data = yield Recv(client, 65536)
        if not data:
            break
        yield Send(client, data)
    print 'Client closed'
    client.close()


def server(port):
    print "Server starting"
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('', port))
    sock.listen(5)
    while True:
        client, addr = yield Accept(sock)
        yield NewTask(handle_client(client, addr))

if __name__ == '__main__':
    sched = Scheduler()
    sched.new(server(45000))
    sched.mainloop()

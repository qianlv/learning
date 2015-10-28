# encoding=utf-8

import socket
from pyos7 import Scheduler


def tcp_connect(hostname, server):
    hostname = hostname or None
    addrinfo = socket.getaddrinfo(
        hostname,
        server,
        socket.AF_UNSPEC,
        socket.SOCK_STREAM,
    )

    sock = None
    for family, socktype, proto, _, sockaddr in addrinfo:
        try:
            sock = socket.socket(family, socktype, proto)
        except socket.error:
            continue

        try:
            sock.connect(sockaddr)
        except socket.error:
            sock.close()
            sock = None

        if sock:
            break
    return sock


def client():
    a_client = tcp_connect('127.0.0.1', 45000)
    a_client.send('abc')
    print a_client.recv(1024)
    yield

if __name__ == '__main__':
    sched = Scheduler()
    sched.new(client())
    sched.mainloop()

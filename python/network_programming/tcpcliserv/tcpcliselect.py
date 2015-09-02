""" a simple asynchronous tcp client """
# encoding=utf-8

import socket
# import time
import signal
import sys
import select
from lib import entry_retry

MAX_RECV = 16


def readn(client_sock, size):
    data = entry_retry(client_sock.recv, size)
    return data


def str_cli(client_sock):
    while True:
        rlist, _, _ = entry_retry(
            select.select,
            [sys.stdin, client_sock],
            [],
            []
        )

        print rlist
        if sys.stdin in rlist:
            msg = sys.stdin.read()
            if not msg:
                break
            client_sock.sendall(msg)

        if client_sock in rlist:
            res_msg = readn(client_sock, MAX_RECV)
            if not res_msg:
                break
            print res_msg


def handle_sigpip(sig, stack):
    print "recived a sigpipe signal"
    return


def client(address):
    client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    signal.signal(signal.SIGPIPE, handle_sigpip)
    client_sock.connect(address)
    str_cli(client_sock)


if __name__ == '__main__':
    client(('localhost', 8888))

# encoding=utf-8

import socket
# import time
import signal
import sys
import select
from lib import entry_retry

MAX_RECV = 16


def readn(client_sock, size):
    res_data = ''
    nleft = size
    while True:
        data = entry_retry(client_sock.recv, min(nleft, MAX_RECV))
        nleft -= len(data)
        res_data += data
        if not data or nleft <= 0:
            break
    return res_data


def str_cli(client_sock):
    while True:
        rlist, _, _ = entry_retry(
            select.select,
            [sys.stdin, client_sock],
            [],
            []
        )

        print rlist
        # XXX: msg_size 可能被覆盖, 如果在读取socket中的数据之前
        # 先从stdin中读取了数据.
        if sys.stdin in rlist:
            msg = sys.stdin.read()
            if not msg:
                break
            client_sock.sendall(msg)
            msg_size = len(msg)
            print msg_size

        if client_sock in rlist:
            res_msg = readn(client_sock, msg_size)
            if not res_msg:
                break
            msg_size = 0
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

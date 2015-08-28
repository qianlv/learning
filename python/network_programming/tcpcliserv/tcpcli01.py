# encoding=utf-8

import socket
# import time
import sys
from lib import entry_retry

MAX_RECV = 16


def readn(client_sock, size):
    nleft = size
    res_data = ''
    while nleft > 0:
        data = entry_retry(client_sock.recv, min(nleft, MAX_RECV))
        res_data += data
        nleft -= len(data)
    return res_data


def str_cli(client_sock):
    while True:
        msg = entry_retry(sys.stdin.read)
        if not msg:
            break
        client_sock.sendall(msg)
        # time.sleep(1)
        # client_sock.sendall(msg)
        res_msg = readn(client_sock, len(msg))
        print res_msg


def client(address):
    client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_sock.connect(address)
    str_cli(client_sock)


if __name__ == '__main__':
    client(('localhost', 8888))

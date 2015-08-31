# encoding=utf-8

import socket
# import time
import signal
import sys
import os
import select
from lib import entry_retry

MAX_RECV = 1024


def readn(client_sock, size):
    data = entry_retry(client_sock.recv, MAX_RECV)
    return data


def str_cli(client_sock):
    stdineof = False
    rl = [sys.stdin, client_sock]
    while True:
        rlist, _, _ = entry_retry(
            select.select, rl, [], []
        )

        print rlist
        if sys.stdin in rlist:
            msg = sys.stdin.readline()
            if not msg:
                stdineof = True
                client_sock.shutdown(socket.SHUT_WR)
                rl.remove(sys.stdin)
                continue
            client_sock.sendall(msg)

        if client_sock in rlist:
            res_msg = readn(client_sock, MAX_RECV)
            if not res_msg:
                if stdineof:
                    return
                os.exit("str_cli: server terminated prematurely")
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
